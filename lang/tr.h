/* tr.h - DOS Coreutils Turkish Language header file
   Written by Ercan Ersoy. */

#define TR 2

#if LANGUAGE == TR
   #define STRING_BASE64_ARGUMENTS "  -d, --decode          decode data\r\n  -i, --ignore-garbage  when decoding, ignore non-alphabet characters\r\n  -w, --wrap=COLS       wrap encoded lines after COLS character (default 76).\r\n                        Use 0 to disable line wrapping\r\n\r\n"
   #define STRING_BASE64_CLOSING_STANDARD_INPUT "closing standard input"
   #define STRING_BASE64_DESCRIPTION "\r\nThe data are encoded as described for the %s alphabet in RFC 4648.\r\nWhen decoding, the input may contain newlines in addition to the bytes of\r\nthe formal %s alphabet.  Use --ignore-garbage to attempt to recover\r\nfrom any other non-alphabet bytes in the encoded stream.\r\n"
   #define STRING_BASE64_EXTRA_OPERAND "extra operand %s"
   #define STRING_BASE64_INVALID_INPUT "invalid input"
   #define STRING_BASE64_INVALID_WRAP_SIZE "invalid wrap size"
   #define STRING_BASE64_READ_ERROR "read error"
   #define STRING_BASE64_USAGE "Usage: %s [OPTION]... [FILE]\r\nBase%d encode or decode FILE, or standard input, to standard output.\r\n"
   #define STRING_BASE64_WRITE_ERROR "write error"
   #define STRING_BEEP_FREQUENCY "  -f Frekans: Sesin frekans�n� tan�mlar."
   #define STRING_BEEP_LENGTH "  -l Uzunluk: Sesin uzunlu�unu milisaniye olarak belirtir."
   #define STRING_BEEP_USAGE "  beep [Se�enekler]"
   #define STRING_BEEP_DESCRIPTION "beep - PC hoparl�r�nden ses ��kt� verir."
   #define STRING_CAN_NOT_COPY "%s kopyalanam�yor.\r\n"
   #define STRING_CAT_DESCRIPTION  "cat - Tan�mlanan dosyan�n i�eri�ini ��kt� verir."
   #define STRING_CAT_ENDS "  -E: Sonlar \"$\" olarak g�r�n�r."
   #define STRING_CAT_TABS "  -T: Sekmeler \"^I\" olarak g�r�n�r."
   #define STRING_CAT_USAGE "  cat [Se�enekler] Dosya"
   #define STRING_CLEAR_DESCRIPTION "clear - U�birim ekran�n� temizler."
   #define STRING_CP_DESCRIPTION "cp - Tan�mlanan dosyan� ya da dizini belirtilen dizine kopyalar."
   #define STRING_CP_USAGE "  cp Kaynak Hedef"
   #define STRING_DATE_DEFAULT_FORMAT "        Varsay�lan bi�im ISO t�r�d�r."
   #define STRING_DATE_DESCRIPTION "date - System tarihini ve saatini yazd�r�r ya da de�i�tirir."
   #define STRING_DATE_EXAMPLE_FORMAT "        �nrek: \"%d-%d-%d %d:%d%:%d\""
   #define STRING_DATE_FORMAT "Bi�im  Tan�mlanan bi�imde s�zce ��kt�lar. S�zce bi�imi, C printf t�r�d�r."
   #define STRING_DATE_SET_TIME_AND_DATE "-s  Sistem tarihini ve saatini de�i�tirir."
   #define STRING_DATE_USAGE_1 "  date [Bi�im]"
   #define STRING_DATE_USAGE_2 "  date -s [Bi�im]"
   #define STRING_DIRNAME_ZERO "  -z, --zero: Her ��kt� sat�r� yeni sat�rla de�il NUL ile biter."
   #define STRING_DIRNAME_DESCRIPTION "dirname - Dosya ismi son ekini atar."
   #define STRING_DIRNAME_EXAMPLE_1 "  dirname C:\\dizin1\\dizin2      -> \"C:\\dir1\""
   #define STRING_DIRNAME_EXAMPLE_2 "  dirname dizin1\\str dizin2\\str -> \"dir1\" taraf�ndan takip eden \"dir2\""
   #define STRING_DIRNAME_EXAMPLE_3 "  dirname autoexec.bat          -> \".\""
   #define STRING_DIRNAME_USAGE_1 "  dirname %s [Se�enek] Ad..."
   #define STRING_DIRNAME_USAGE_2 "E�er, ad hi�bir \\ i�ermiyorsa, her bir ad, son e�ik olmayan bile�eni"
   #define STRING_DIRNAME_USAGE_3 "bile�eni ve takip eden e�ik �izgileri ��kar�lm�� olarak '.'"
   #define STRING_DIRNAME_USAGE_4 "��kt�lan�r (ge�erli dizini ifade eder)."
   #define STRING_ECHO_CHARACTERS_ARE "    Karakterler: \\a \\b \\c \\e \\f \\r \\t \\v"
   #define STRING_ECHO_DESCRIPTION "echo - Belirtilen iletileri yazd�r�r."
   #define STRING_ECHO_NEWLINE_CHARACTER "-n  Ek olarak, yeni sat�r karakteri yazd�r�r."
   #define STRING_ECHO_SPECIAL_CHARACTERS "-e  Prints special characters. Message must be quoted."
   #define STRING_ECHO_USAGE "  echo [Se�enekler] �letiler"
   #define STRING_EMIT_TRY_HELP "Daha fazla bilgi i�in %s --help sat�r�n� deneyin.\n"
   #define STRING_EXAMPLES "�rnekler:"
   #define STRING_FALSE_DESCRIPTION "false - Bir ba�ar�s�zl�k d�nd�r�r."
   #define STRING_DOES_NOT_DIRECTORY "%s dizin de�il.\r\n"
   #define STRING_DOS_COREUTILS_VERSION "DOS Coreutils S�r�m�: 0.6"
   #define STRING_HELP_DOS_COREUTILS_COMMANDS "DOS Coreutils Komutlar�:\r\n"
   #define STRING_HELP_OPTION_DESCRIPTION "  --help: Bu yard�m bilgisini g�r�nt�ler ve ��kar."
   #define STRING_INVALID_SYNTAX "Ge�ersiz s�zdizim."
   #define STRING_LIB_XBIN_IO_ERROR "failed to set file descriptor text/binary mode"
   #define STRING_LS_DESCRIPTION "ls - Dizin i�eri�ini yazd�r�r."
   #define STRING_LS_DISPLAY_LONG_LISTING_FORMAT "-l  Uzun listeleme bi�iminde g�r�nt�ler."
   #define STRING_LS_DISPLAY_OUTPUT_AS_ONE_COLUMN "-1  Bir s�tun olarak ��kt�y� g�r�nt�ler."
   #define STRING_LS_DO_NOT_IGNORE "-a  \".\"'lar� ve \"..\"'lar� g�rmezden gelmez."
   #define STRING_LS_USAGE "  ls [Se�enekler] [Dosya]"
   #define STRING_MISSING_OPERAND "��le� eksik.\n"
   #define STRING_MKDIR_CAN_NOT_CREATE_DIRECTORY "%s dizini olu�turulam�yor.\r\n"
   #define STRING_MKDIR_DESCRIPTION "mkdir - Belirtilen dizinleri olu�turur."
   #define STRING_MKDIR_USAGE "  mkdir Directories"
   #define STRING_MV_CAN_NOT_MOVE "%s ta��nam�yor.\r\n"
   #define STRING_MV_DESCRIPTION_1 "mv - Tan�mlanan dosya ya da dizini"
   #define STRING_MV_DESCRIPTION_2 "belirtilen dizine ta��r ve/ya da de�i�tirir."
   #define STRING_MV_USAGE "  mv Kaynak Hedef"
   #define STRING_NO_ENOUGH_ARGUMENTS "Arg�manlar yeterli de�il.\r\n"
   #define STRING_NOTE "Not:"
   #define STRING_OPTION "Se�enek:"
   #define STRING_OPTIONS "Se�enekler:"
   #define STRING_PWD_DESCRIPTION "pwd - Ge�erli dizinin ad�n� yazd�r�r."
   #define STRING_RM_CAN_NOT_REMOVE "%s silinemiyor.\r\n"
   #define STRING_RM_DESCRIPTION "rm - Belirtilen dizinleri siler."
   #define STRING_RM_REMOVE_RECURSIVELY "-r  Tan�mlanan dizinleri ve i�indekileri �zyinelemeli siler."
   #define STRING_RM_USAGE "  rm [-r] Elemanlar"
   #define STRING_RMDIR_CAN_NOT_REMOVE "%s dizini silinemiyor.\r\n"
   #define STRING_RMDIR_DESCRIPTION "rmdir - Belirtilen dizinleri siler."
   #define STRING_RMDIR_DIRECTORY_CAN_NOT_BE_REMOVED "%s dizini silinemiyor.\r\n"
   #define STRING_RMDIR_USAGE "  rmdir Dizinler"
   #define STRING_SH_DESCRIPTION "sh - DOS Coreuils kabu�u"
   #define STRING_SH_TYPE_EXIT "  DOS Coreutils kabu�unda ��kmak i�in \"exit\" komutunu verin."
   #define STRING_TIME_ARGUMENTS "  time Komut [Arg�man]"
   #define STRING_TIME_DESCRIPTION "time - Belirtilen komutun �al��t�r�lma zaman�n� saniye olarak �l�er."
   #define STRING_TOO_MUCH_ARGUMENTS "�ok fazla arg�man.\r\n"
   #define STRING_TRUE_DESCRIPTION "true - Bir ba�ar� d�nd�r�r."
   #define STRING_VERSION_OPTION_DESCRIPTION "  --version: S�r�m bilgisini g�r�nt�ler ve ��kar."
#endif
