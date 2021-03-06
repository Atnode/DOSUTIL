/* Base64 encode/decode strings or files.
   Copyright (C) 2004-2018 Free Software Foundation, Inc.
   This file is part of Base64.
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/* Written by Simon Josefsson <simon@josefsson.org>.  */
/* Ported to FreeDOS by LiquidFox1776 */

#if BASE_TYPE == 32
# define PROGRAM_NAME "base32"
#else
# define BASE_TYPE 64
# define PROGRAM_NAME "base64"
#endif

#include "system.h"
#include <string.h>
#include "..\lib\die.h"
#include "..\lib\error.h"
#include "..\gl\fadvise.h"
//#include "..\lib\quote.h" TODO Implement quote
#include "..\lib\xstrtol.h"
#include "..\gl\xdec2int.h"
#include "..\lib\xbin-io.h"
#include "..\lib\getopt.h"

#if BASE_TYPE == 32
# include "..\lib\base32.h"
#else
# include "..\lib\base64.h"
#endif

//#define AUTHORS proper_name ("Simon Josefsson")
#define AUTHORS "Simon Josefsson"

static struct option const long_options[] =
{
  {"decode", no_argument, 0, 'd'},
  {"wrap", required_argument, 0, 'w'},
  {"ignore-garbage", no_argument, 0, 'i'},

  {GETOPT_HELP_OPTION_DECL},
  {GETOPT_VERSION_OPTION_DECL},
  {NULL, 0, NULL, 0}
};

char *nls_string; /* pointer for the nls strings */

void
usage (int status)
{
  if (status != EXIT_SUCCESS)
    emit_try_help ();
  else
    {
     nls_string =  get_nls_string(0,8,"Usage: %s [OPTION]... [FILE]\r\nBase%d encode or decode FILE, or standard input, to standard output.\r\n");
      printf (nls_string, PROGRAM_NAME, BASE_TYPE);

      emit_stdin_note ();
      emit_mandatory_arg_note ();
      
      nls_string = get_nls_string(0, 1,"  -d, --decode          decode data\r\n  -i, --ignore-garbage  when decoding, ignore non-alphabet characters\r\n  -w, --wrap=COLS       wrap encoded lines after COLS character (default 76).\r\n                        Use 0 to disable line wrapping\r\n\r\n");
      fputs ( nls_string, stdout);
      fputs (get_nls_string(0,10,"  --help: Display this help and exit."), stdout);
      fputs ("\n", stdout);
      fputs (get_nls_string(0,11,"  --version: Display version information and exit."), stdout);
      fputs ("\n", stdout);
      nls_string = get_nls_string(0,3,"\r\nThe data are encoded as described for the %s alphabet in RFC 4648.\r\nWhen decoding, the input may contain newlines in addition to the bytes of\r\nthe formal %s alphabet.  Use --ignore-garbage to attempt to recover\r\nfrom any other non-alphabet bytes in the encoded stream.\r\n");
      printf (nls_string,PROGRAM_NAME, PROGRAM_NAME);
      //emit_ancillary_info (PROGRAM_NAME);
    }
  close_nls_file(true);
  exit (status);
}

#define ENC_BLOCKSIZE (1024*3*10) // 30720

#if BASE_TYPE == 32
# define BASE_LENGTH BASE32_LENGTH
/* Note that increasing this may decrease performance if --ignore-garbage
   is used, because of the memmove operation below.  */
# define DEC_BLOCKSIZE (1024*5) //5120

/* Ensure that BLOCKSIZE is a multiple of 5 and 8.  */
verify (ENC_BLOCKSIZE % 40 == 0);  /* So padding chars only on last block.  */
verify (DEC_BLOCKSIZE % 40 == 0);  /* So complete encoded blocks are used.  */

# define base_encode base32_encode
# define base_decode_context base32_decode_context
# define base_decode_ctx_init base32_decode_ctx_init
# define base_decode_ctx base32_decode_ctx
# define isbase isbase32
#else
# define BASE_LENGTH BASE64_LENGTH
/* Note that increasing this may decrease performance if --ignore-garbage
   is used, because of the memmove operation below.  */
# define DEC_BLOCKSIZE (1024*3) //1536 3072

/* Ensure that BLOCKSIZE is a multiple of 3 and 4.  */
verify (ENC_BLOCKSIZE % 12 == 0);  /* So padding chars only on last block.  */
verify (DEC_BLOCKSIZE % 12 == 0);  /* So complete encoded blocks are used.  */

# define base_encode base64_encode
# define base_decode_context base64_decode_context
# define base_decode_ctx_init base64_decode_ctx_init
# define base_decode_ctx base64_decode_ctx
# define isbase isbase64
#endif

static void
wrap_write (const char *buffer, size_t len,
            uintmax_t wrap_column, size_t *current_column, FILE *out)
{
  size_t written;

  if (wrap_column == 0)
    {
      /* Simple write. */
      if (fwrite (buffer, 1, len, stdout) < len)
        die (EXIT_FAILURE, errno, (get_nls_string(0,9,"write error")));
    }
  else
    for (written = 0; written < len;)
      {
        uintmax_t cols_remaining = wrap_column - *current_column;
        size_t to_write = MIN (cols_remaining, SIZE_MAX);
        to_write = MIN (to_write, len - written);

        if (to_write == 0)
          {
            if (fputc ('\n', out) == EOF)
              die (EXIT_FAILURE, errno, (get_nls_string(0,9,"write error")));
            *current_column = 0;
          }
        else
          {
            if (fwrite (buffer + written, 1, to_write, stdout) < to_write)
              die (EXIT_FAILURE, errno, (get_nls_string(0,9,"write error")));
            *current_column += to_write;
            written += to_write;
          }
      }
}

static void
do_encode (FILE *in, FILE *out, uintmax_t wrap_column)
{
  size_t current_column = 0;
  char inbuf[ENC_BLOCKSIZE];
  #if BASE_TYPE == 32
  char outbuf[49152];
  #else
  char outbuf[40960]; // char outbuf[BASE_LENGTH (ENC_BLOCKSIZE)];
  #endif

  size_t sum;

  do
    {
      size_t n;

      sum = 0;
      do
        {
          n = fread (inbuf + sum, 1, ENC_BLOCKSIZE - sum, in);
          sum += n;
        }
      while (!feof (in) && !ferror (in) && sum < ENC_BLOCKSIZE);

      if (sum > 0)
        {
          /* Process input one block at a time.  Note that ENC_BLOCKSIZE
             is sized so that no pad chars will appear in output. */
          base_encode (inbuf, sum, outbuf, BASE_LENGTH(sum));

          wrap_write (outbuf, BASE_LENGTH (sum), wrap_column,
                      &current_column, out);
        }
    }
  while (!feof (in) && !ferror (in) && sum == ENC_BLOCKSIZE);

  /* When wrapping, terminate last line. */
  if (wrap_column && current_column > 0 && fputc ('\n', out) == EOF)
    die (EXIT_FAILURE, errno, (get_nls_string(0,9,"write error")));

  if (ferror (in))
    die (EXIT_FAILURE, errno, (get_nls_string(0,7,"read error")));
}

static void
do_decode (FILE *in, FILE *out, bool ignore_garbage)
{
  char inbuf[BASE_LENGTH (DEC_BLOCKSIZE)];
  char outbuf[DEC_BLOCKSIZE];
  size_t sum, i;
  struct base_decode_context ctx;

  base_decode_ctx_init (&ctx);

  do
    {
      bool ok;
      size_t n;
      unsigned int k;

      sum = 0;
      do
        {
          n = fread (inbuf + sum, 1, BASE_LENGTH (DEC_BLOCKSIZE) - sum, in);

          if (ignore_garbage)
            {
              for (i = 0; n > 0 && i < n;)
                {
                  if (isbase (inbuf[sum + i]) || inbuf[sum + i] == '=')
                    i++;
                  else
                    memmove (inbuf + sum + i, inbuf + sum + i + 1, --n - i);
                }
            }

          sum += n;

          if (ferror (in))
            die (EXIT_FAILURE, errno, (get_nls_string(0,7,"read error")));
        }
      while (sum < BASE_LENGTH (DEC_BLOCKSIZE) && !feof (in));

      /* The following "loop" is usually iterated just once.
         However, when it processes the final input buffer, we want
         to iterate it one additional time, but with an indicator
         telling it to flush what is in CTX.  */
      for (k = 0; k < 1 + !!feof (in); k++)
        {
          if (k == 1 && ctx.i == 0)
            break;
          n = DEC_BLOCKSIZE;
          ok = base_decode_ctx (&ctx, inbuf, (k == 0 ? sum : 0), outbuf, &n);

          if (fwrite (outbuf, 1, n, out) < n)
            die (EXIT_FAILURE, errno, (get_nls_string(0,9,"write error")));

          if (!ok)
            die (EXIT_FAILURE, 0, (get_nls_string(0,5,"invalid input")));
        }
    }
  while (!feof (in));
}

int
main (int argc, char **argv)
{
  int opt;
  FILE *input_fh;
  const char *infile;

  /* True if --decode has been given and we should decode data. */
  bool decode = false;
  /* True if we should ignore non-base-alphabetic characters. */
  bool ignore_garbage = false;
  /* Wrap encoded data around the 76:th column, by default. */
  uintmax_t wrap_column = 76;

  open_nls_file("", PROGRAM_NAME);
  
  while ((opt = getopt_long (argc, argv, "diw:", long_options, NULL)) != -1)
    switch (opt)
      {
      case 'd':
        decode = true;
        break;

      case 'w':
       wrap_column = xdectoumax (optarg, 0, UINTMAX_MAX, "",
                                  (get_nls_string(0,6,"invalid wrap size")), 0);
        break;

      case 'i':
        ignore_garbage = true;
        break;

      case_GETOPT_HELP_CHAR;
      case_GETOPT_VERSION_CHAR(PROGRAM_NAME, AUTHORS);

      default:
        usage (EXIT_FAILURE);
        break;
      }

  if (argc - optind > 1)
    {
      error (0, 0, (get_nls_string(0,4,"extra operand %s")), argv[optind]);//quote (argv[optind]));
      usage (EXIT_FAILURE);
    }

  if (optind < argc)
    infile = argv[optind];
  else
    infile = "-";

  if (STREQ (infile, "-"))
    {
      xset_binary_mode (STDIN_FILENO, O_BINARY); //calls setmode
      input_fh = stdin;
    }
  else
    {
      input_fh = fopen (infile, "rb");
      if (input_fh == NULL)
        die (EXIT_FAILURE, errno, "%s", infile); //quotef (infile));
    }

  fadvise (input_fh, FADVISE_SEQUENTIAL);

  if (decode)
    do_decode (input_fh, stdout, ignore_garbage);
 else
    do_encode (input_fh, stdout, wrap_column);

  if (fclose (input_fh) == EOF)
    {
      if (STREQ (infile, "-")){
        die (EXIT_FAILURE, errno, (get_nls_string(0,2,"closing standard input")));
        }
      else{
        die (EXIT_FAILURE, errno, "%s", infile);// quotef (infile) );
        }
    }

    close_nls_file(true);
  return EXIT_SUCCESS;
}

