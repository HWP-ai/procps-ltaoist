/* top_nls.c - provide the basis for future nls translations */
/*
 * Copyright (c) 2011-2012,     by: James C. Warner
 *    All rights reserved.      8921 Hilloway Road
 *                              Eden Prairie, Minnesota 55347 USA
 *
 * This file may be used subject to the terms and conditions of the
 * GNU Library General Public License Version 2, or any later version
 * at your option, as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 */
/* For contributions to this program, the author wishes to thank:
 *    Craig Small, <csmall@small.dropbear.id.au>
 *    Sami Kerola, <kerolasa@iki.fi>
 */

#include <locale.h>
#include <stdio.h>
#ifdef VALIDATE_NLS
#include <stdlib.h>
#endif
#include <string.h>

#include "../include/nls.h"

#include "top.h"
#include "top_nls.h"

        // Programmer Note(s):
        //  Preparation ---------------------------------------------
        //    Unless you have *something* following the gettext macro,
        //    xgettext will refuse to see any TRANSLATORS comments.
        //    Thus empty strings have been added for potential future
        //    comment additions.
        //
        //    Also, by omitting the argument for the --add-comments
        //    XGETTEXT_OPTION in po/Makevars, *any* preceding c style
        //    comment will be propagated to the .pot file, providing
        //    that the gettext macro isn't empty as discussed above.
        //    However, this is far too aggressive so we have chosen
        //    the word 'Translation' to denote xgettext comments.
        //
        //    /* Need Not Say 'TRANSLATORS': ...
        //    snprintf(buf, sizeof(buf), "%s", _(      // unseen comment
        //
        //    /* Translation Hint: ...
        //    snprintf(buf, sizeof(buf), "%s", _(""    // now it's seen!
        //
        //  Translation, from po/ directory after make --------------
        //  ( this is the procedure used before any translations were  )
        //  ( available in the po/ directory, which contained only the )
        //  ( procps-ng.pot, this domain's template file.              )
        //
        //  ( below: ll_CC = language/country as in 'zh_CN' or 'en_AU' )
        //
        //    msginit --locale=ll_CC --no-wrap
        //     . creates a ll_CC.po file from the template procps-ng.pot
        //     . may also duplicate msgid as msgstr if languages similar
        //    msgen --no-wrap ll_CC.po --output-file=ll_CC.po
        //     . duplicates every msgid literal as msgstr value
        //     . this is the file that's edited
        //        . replace "Content-Type: ... charset=ASCII\n"
        //                           with "... charset=UTF-8\n"
        //        . translate msgstr values, leaving msgid unchanged
        //    msgfmt ll_CC.po --strict --output-file=procps-ng.mo
        //     . after which chmod 644
        //     . move to /usr/share/local/ll_CC/LC_MESSAGES/ directory
        //
        //  Testing -------------------------------------------------
        //    export LC_ALL= && export LANGUAGE=ll_CC
        //    run some capable program like top
        //

        /*
         * These are our string tables with the following contents:
         *    Head : column headings with varying size limits
         *    Desc : fields descriptions not to exceed 20 screen positions
         *    Norm : regular text possibly also containing c-format specifiers
         *    Uniq : show_special specially formatted strings
         *
         * The latter table presents the greatest translation challenge !
         *
         * We go to the trouble of creating the nls string tables to achieve
         * these objectives:
         *    +  the overhead of repeated runtime calls to gettext()
         *       will be avoided
         *    +  the order of the strings in the template (.pot) file
         *       can be completely controlled
         *    +  none of the important translator only comments will
         *       clutter and obscure the main program
         */
const char *Head_nlstab[P_MAXPFLGS];
const char *Desc_nlstab[P_MAXPFLGS];
const char *Norm_nlstab[norm_MAX];
const char *Uniq_nlstab[uniq_MAX];


        /*
         * This routine builds the nls table containing plain text only
         * used as the field descriptions.  Each translated line MUST be
         * kept to a maximum of 20 characters or less! */
static void build_two_nlstabs (void) {

/* Translation Notes ------------------------------------------------
   .  It is strongly recommend that the --no-wrap command line option
   .  be used with all supporting translation tools, when available.
   .
   .  The following line pairs contain only plain text and consist of:
   .     1) a field name/column header - mostly upper case
   .     2) the related description    - both upper and lower case
   .
   .  To avoid truncation at runtime, each column header is noted with
   .  its maximum size and the following description must not exceed
   .  20 characters.  Fewer characters are ok.
   .
   . */

/* Translation Hint: maximum 'PID' = 5 */
   Head_nlstab[P_PID] = _("PID");
   Desc_nlstab[P_PID] = _("Process Id");
/* Translation Hint: maximum 'PPID' = 5 */
   Head_nlstab[P_PPD] = _("PPID");
   Desc_nlstab[P_PPD] = _("Parent Process pid");
/* Translation Hint: maximum 'UID' = 5 */
   Head_nlstab[P_UED] = _("UID");
   Desc_nlstab[P_UED] = _("Effective User Id");
/* Translation Hint: maximum 'USER' = 8 */
   Head_nlstab[P_UEN] = _("USER");
   Desc_nlstab[P_UEN] = _("Effective User Name");
/* Translation Hint: maximum 'RUID' = 5 */
   Head_nlstab[P_URD] = _("RUID");
   Desc_nlstab[P_URD] = _("Real User Id");
/* Translation Hint: maximum 'RUSER' = 8 */
   Head_nlstab[P_URN] = _("RUSER");
   Desc_nlstab[P_URN] = _("Real User Name");
/* Translation Hint: maximum 'SUID' = 5 */
   Head_nlstab[P_USD] = _("SUID");
   Desc_nlstab[P_USD] = _("Saved User Id");
/* Translation Hint: maximum 'SUSER' = 8 */
   Head_nlstab[P_USN] = _("SUSER");
   Desc_nlstab[P_USN] = _("Saved User Name");
/* Translation Hint: maximum 'GID' = 5 */
   Head_nlstab[P_GID] = _("GID");
   Desc_nlstab[P_GID] = _("Group Id");
/* Translation Hint: maximum 'GROUP' = 8 */
   Head_nlstab[P_GRP] = _("GROUP");
   Desc_nlstab[P_GRP] = _("Group Name");
/* Translation Hint: maximum 'PGRP' = 5 */
   Head_nlstab[P_PGD] = _("PGRP");
   Desc_nlstab[P_PGD] = _("Process Group Id");
/* Translation Hint: maximum 'TTY' = 8 */
   Head_nlstab[P_TTY] = _("TTY");
   Desc_nlstab[P_TTY] = _("Controlling Tty");
/* Translation Hint: maximum 'TPGID' = 5 */
   Head_nlstab[P_TPG] = _("TPGID");
   Desc_nlstab[P_TPG] = _("Tty Process Grp Id");
/* Translation Hint: maximum 'SID' = 5 */
   Head_nlstab[P_SID] = _("SID");
   Desc_nlstab[P_SID] = _("Session Id");
/* Translation Hint: maximum 'PR' = 3 */
   Head_nlstab[P_PRI] = _("PR");
   Desc_nlstab[P_PRI] = _("Priority");
/* Translation Hint: maximum 'NI' = 3 */
   Head_nlstab[P_NCE] = _("NI");
   Desc_nlstab[P_NCE] = _("Nice Value");
/* Translation Hint: maximum 'nTH' = 3 */
   Head_nlstab[P_THD] = _("nTH");
   Desc_nlstab[P_THD] = _("Number of Threads");
/* Translation Hint: maximum 'P' = 1 */
   Head_nlstab[P_CPN] = _("P");
   Desc_nlstab[P_CPN] = _("Last Used Cpu (SMP)");
/* Translation Hint: maximum '%CPU' = 4 */
   Head_nlstab[P_CPU] = _("%CPU");
   Desc_nlstab[P_CPU] = _("CPU Usage");
/* Translation Hint: maximum '' = 6 */
   Head_nlstab[P_TME] = _("TIME");
   Desc_nlstab[P_TME] = _("CPU Time");
/* Translation Hint: maximum 'TIME+' = 9 */
   Head_nlstab[P_TM2] = _("TIME+");
   Desc_nlstab[P_TM2] = _("CPU Time, hundredths");
/* Translation Hint: maximum '%MEM' = 4 */
   Head_nlstab[P_MEM] = _("%MEM");
   Desc_nlstab[P_MEM] = _("Memory Usage (RES)");
/* Translation Hint: maximum 'VIRT' = 5 */
   Head_nlstab[P_VRT] = _("VIRT");
   Desc_nlstab[P_VRT] = _("Virtual Image (KiB)");
/* Translation Hint: maximum 'SWAP' = 4 */
   Head_nlstab[P_SWP] = _("SWAP");
   Desc_nlstab[P_SWP] = _("Swapped Size (KiB)");
/* Translation Hint: maximum 'RES' = 4 */
   Head_nlstab[P_RES] = _("RES");
   Desc_nlstab[P_RES] = _("Resident Size (KiB)");
/* Translation Hint: maximum 'CODE' = 4 */
   Head_nlstab[P_COD] = _("CODE");
   Desc_nlstab[P_COD] = _("Code Size (KiB)");
/* Translation Hint: maximum 'DATA' = 4 */
   Head_nlstab[P_DAT] = _("DATA");
   Desc_nlstab[P_DAT] = _("Data+Stack (KiB)");
/* Translation Hint: maximum 'SHR' = 4 */
   Head_nlstab[P_SHR] = _("SHR");
   Desc_nlstab[P_SHR] = _("Shared Memory (KiB)");
/* Translation Hint: maximum 'nMaj' = 4 */
   Head_nlstab[P_FL1] = _("nMaj");
   Desc_nlstab[P_FL1] = _("Major Page Faults");
/* Translation Hint: maximum 'nMin' = 4 */
   Head_nlstab[P_FL2] = _("nMin");
   Desc_nlstab[P_FL2] = _("Minor Page Faults");
/* Translation Hint: maximum 'nDRT' = 4 */
   Head_nlstab[P_DRT] = _("nDRT");
   Desc_nlstab[P_DRT] = _("Dirty Pages Count");
/* Translation Hint: maximum 'S' = 1 */
   Head_nlstab[P_STA] = _("S");
   Desc_nlstab[P_STA] = _("Process Status");
/* Translation Hint: maximum 'COMMAND' = 7 */
   Head_nlstab[P_CMD] = _("COMMAND");
   Desc_nlstab[P_CMD] = _("Command Name/Line");
/* Translation Hint: maximum 'WCHAN' = 7 */
   Head_nlstab[P_WCH] = _("WCHAN");
   Desc_nlstab[P_WCH] = _("Sleeping in Function");
/* Translation Hint: maximum 'Flags' = 8 */
   Head_nlstab[P_FLG] = _("Flags");
   Desc_nlstab[P_FLG] = _("Task Flags <sched.h>");
/* Translation Hint: maximum 'CGROUPS' = 7 */
   Head_nlstab[P_CGR] = _("CGROUPS");
   Desc_nlstab[P_CGR] = _("Control Groups");
/* Translation Hint: maximum 'SUPGIDS' = 7 */
   Head_nlstab[P_SGD] = _("SUPGIDS");
   Desc_nlstab[P_SGD] = _("Supp Groups IDs");
/* Translation Hint: maximum 'SUPGRPS' = 7 */
   Head_nlstab[P_SGN] = _("SUPGRPS");
   Desc_nlstab[P_SGN] = _("Supp Groups Names");
/* Translation Hint: maximum 'TGID' = 5 */
   Head_nlstab[P_TGD] = _("TGID");
   Desc_nlstab[P_TGD] = _("Thread Group Id");
#ifdef OOMEM_ENABLE
/* Translation Hint: maximum 'Adj' = 3 */
   Head_nlstab[P_OOA] = _("Adj");
   Desc_nlstab[P_OOA] = _("oom_adjustment (2^X)");
/* Translation Hint: maximum 'Badness' = 8 */
   Head_nlstab[P_OOM] = _("Badness");
   Desc_nlstab[P_OOM] = _("oom_score (badness)");
#endif
/* Translation Hint: maximum 'ENVIRON' = 7 */
   Head_nlstab[P_ENV] = _("ENVIRON");
/* Translation Hint: the abbreviation 'vars' below is shorthand for
                     'variables' */
   Desc_nlstab[P_ENV] = _("Environment vars");
/* Translation Hint: maximum 'vMj' = 3 */
   Head_nlstab[P_FV1] = _("vMj");
   Desc_nlstab[P_FV1] = _("Major Faults delta");
/* Translation Hint: maximum 'vMn' = 3 */
   Head_nlstab[P_FV2] = _("vMn");
   Desc_nlstab[P_FV2] = _("Minor Faults delta");
}


        /*
         * This routine builds the nls table containing both plain text
         * and regular c-format strings. */
static void build_norm_nlstab (void) {

/* Translation Notes ------------------------------------------------
   .  It is strongly recommend that the --no-wrap command line option
   .  be used with all supporting translation tools, when available.
   .
   .  This group of lines contains both plain text and c-format strings.
   .
   .  Some strings reflect switches used to affect the running program
   .  and should not be translated without also making corresponding
   .  c-code logic changes.
   . */

   Norm_nlstab[EXIT_signals_fmt] = _("\n"
      "\tsignal %d (%s) was caught by %s, please\n"
      "\tsee http://www.debian.org/Bugs/Reporting\n");
   Norm_nlstab[WRONG_switch_fmt] = _(""
      "inappropriate '%s'\n"
      "usage:\t%s%s");
   Norm_nlstab[HELP_cmdline_fmt] = _(""
      "\t%s\n"
      "usage:\t%s%s");
   Norm_nlstab[FAIL_statopn_fmt] = _("failed /proc/stat open: %s");
   Norm_nlstab[FAIL_openlib_fmt] = _("failed openproc: %s");
   Norm_nlstab[BAD_delayint_fmt] = _("bad delay interval '%s'");
   Norm_nlstab[BAD_niterate_fmt] = _("bad iterations argument '%s'");
   Norm_nlstab[LIMIT_exceed_fmt] = _("pid limit (%d) exceeded");
   Norm_nlstab[BAD_mon_pids_fmt] = _("bad pid '%s'");
   Norm_nlstab[MISSING_args_fmt] = _("-%c requires argument");
   Norm_nlstab[BAD_widtharg_fmt] = _("bad width arg '%s', must > %d");
   Norm_nlstab[UNKNOWN_opts_fmt] = _(""
      "unknown option '%c'\n"
      "usage:\t%s%s");
   Norm_nlstab[DELAY_secure_txt] = _("-d disallowed in \"secure\" mode");
   Norm_nlstab[DELAY_badarg_txt] = _("-d requires positive argument");
   Norm_nlstab[ON_word_only_txt] = _("On");
   Norm_nlstab[OFF_one_word_txt] = _("Off");
/* Translation Hint: Only the following words should be translated
   .                 delay, limit, user, cols (abbreviation for columns)*/
   Norm_nlstab[USAGE_abbrev_txt] = _(" -hv | -bcHiSs -d delay -n limit -u|U user -p pid[,pid] -w [cols]");
   Norm_nlstab[FAIL_statget_txt] = _("failed /proc/stat read");
   Norm_nlstab[FOREST_modes_fmt] = _("Forest mode %s");
   Norm_nlstab[FAIL_tty_get_txt] = _("failed tty get");
   Norm_nlstab[FAIL_tty_mod_fmt] = _("failed Tty_tweaked set: %s");
   Norm_nlstab[FAIL_tty_raw_fmt] = _("failed Tty_raw set: %s");
   Norm_nlstab[CHOOSE_group_txt] = _("Choose field group (1 - 4)");
   Norm_nlstab[DISABLED_cmd_txt] = _("Command disabled, 'A' mode required");
   Norm_nlstab[DISABLED_win_fmt] = _("Command disabled, activate %s with '-' or '_'");
   Norm_nlstab[COLORS_nomap_txt] = _("No colors to map!");
   Norm_nlstab[FAIL_rc_open_fmt] = _("Failed '%s' open: %s");
   Norm_nlstab[WRITE_rcfile_fmt] = _("Wrote configuration to '%s'");
   Norm_nlstab[DELAY_change_fmt] = _("Change delay from %.1f to");
   Norm_nlstab[THREADS_show_fmt] = _("Show threads %s");
   Norm_nlstab[IRIX_curmode_fmt] = _("Irix mode %s");
   Norm_nlstab[GET_pid2kill_fmt] = _("PID to signal/kill [default pid = %d]");
   Norm_nlstab[GET_sigs_num_fmt] = _("Send pid %d signal [%d/sigterm]");
   Norm_nlstab[FAIL_signals_fmt] = _("Failed signal pid '%d' with '%d': %s");
   Norm_nlstab[BAD_signalid_txt] = _("Invalid signal");
   Norm_nlstab[GET_pid2nice_fmt] = _("PID to renice [default pid = %d]");
   Norm_nlstab[GET_nice_num_fmt] = _("Renice PID %d to value");
   Norm_nlstab[FAIL_re_nice_fmt] = _("Failed renice of PID %d to %d: %s");
   Norm_nlstab[NAME_windows_fmt] = _("Rename window '%s' to (1-3 chars)");
   Norm_nlstab[TIME_accumed_fmt] = _("Cumulative time %s");
   Norm_nlstab[GET_max_task_fmt] = _("Maximum tasks = %d, change to (0 is unlimited)");
   Norm_nlstab[BAD_max_task_txt] = _("Invalid maximum");
   Norm_nlstab[HILIGHT_cant_txt] = _("Nothing to highlight!");
   Norm_nlstab[GET_user_ids_txt] = _("Which user (blank for all)");
   Norm_nlstab[UNKNOWN_cmds_txt] = _("Unknown command - try 'h' for help");
   Norm_nlstab[SCROLL_coord_fmt] = _("scroll coordinates: y = %d/%%d (tasks), x = %d/%d (fields)");
   Norm_nlstab[FAIL_alloc_c_txt] = _("failed memory allocate");
   Norm_nlstab[FAIL_alloc_r_txt] = _("failed memory re-allocate");
   Norm_nlstab[BAD_numfloat_txt] = _("Unacceptable floating point");
   Norm_nlstab[BAD_username_txt] = _("Invalid user");
   Norm_nlstab[FAIL_sigstop_fmt] = _("failed sigprocmask, SIG_BLOCK: %s");
   Norm_nlstab[FAIL_sigmask_fmt] = _("failed sigprocmask, SIG_SETMASK: %s");
   Norm_nlstab[FOREST_views_txt] = _("forest view");
   Norm_nlstab[FAIL_widepid_txt] = _("failed pid maximum size test");
   Norm_nlstab[FAIL_widecpu_txt] = _("failed number of cpus test");
   Norm_nlstab[RC_bad_files_fmt] = _("incompatible rcfile, you should delete '%s'");
   Norm_nlstab[RC_bad_entry_fmt] = _("window entry #%d corrupt, please delete '%s'");
   Norm_nlstab[NOT_onsecure_txt] = _("Unavailable in secure mode");
   Norm_nlstab[NOT_smp_cpus_txt] = _("Only 1 cpu detected");
   Norm_nlstab[BAD_integers_txt] = _("Unacceptable integer");
   Norm_nlstab[SELECT_clash_txt] = _("conflicting process selections (U/p/u)");
/* Translation Hint: This is an abbreviation (limit 3 characters) for:
   .                 kibibytes (1024 bytes) */
   Norm_nlstab[AMT_kilobyte_txt] = _("KiB");
/* Translation Hint: This is an abbreviation (limit 3 characters) for:
   .                 mebibytes (1,048,576 bytes) */
   Norm_nlstab[AMT_megabyte_txt] = _("MiB");
/* Translation Hint: This is an abbreviation (limit 3 characters) for:
   .                 gibibytes (1,073,741,824 bytes) */
   Norm_nlstab[AMT_gigabyte_txt] = _("GiB");
   Norm_nlstab[WORD_threads_txt] = _("Threads");
   Norm_nlstab[WORD_process_txt] = _("Tasks");
/* Translation Hint: The following "word" is meant to represent either a single
   .                 cpu or all of the processors in a multi-processor computer
   .                 (should be exactly 6 characters, not counting the colon)*/
   Norm_nlstab[WORD_allcpus_txt] = _("Cpu(s):");
/* Translation Hint: The following "word" is meant to represent a single processor
   .                 (should be exactly 3 characters) */
   Norm_nlstab[WORD_eachcpu_fmt] = _("Cpu%-3d:");
/* Translation Hint: The following word "another" must have 1 trailing space */
   Norm_nlstab[WORD_another_txt] = _("another ");
   Norm_nlstab[FIND_no_next_txt] = _("Locate next inactive, use \"L\"");
   Norm_nlstab[GET_find_str_txt] = _("Locate string");
   Norm_nlstab[FIND_no_find_fmt] = _("%s\"%s\" not found");
   Norm_nlstab[XTRA_fixwide_fmt] = _("width incr is %d, change to (0 default, -1 auto)");
#ifndef WARN_CFG_OFF
   Norm_nlstab[XTRA_warncfg_txt] = _("Overwrite existing old style rcfile?");
#endif
#ifndef INSP_OFFDEMO
   Norm_nlstab[YINSP_demo01_txt] = _("Open Files");
   Norm_nlstab[YINSP_demo02_txt] = _("NUMA Info");
   Norm_nlstab[YINSP_demo03_txt] = _("Log");
   Norm_nlstab[YINSP_demo04_txt] = _(""
      "This is simulated output representing the contents of some file or the output\n"
      "from some command.  Exactly which commands and/or files are solely up to you.\n"
      "\n"
      "Although this text is for information purposes only, it can still be scrolled\n"
      "and searched like real output will be.  You are encouraged to experiment with\n"
      "those features as explained in the prologue above.\n"
      "\n"
      "To enable real Inspect functionality, entries must be added to the end of the\n"
      "top personal personal configuration file.  You could use your favorite editor\n"
      "to accomplish this, taking care not to disturb existing entries.\n"
      "\n"
      "Another way to add entries is illustrated below, but it risks overwriting the\n"
      "rcfile.  Redirected echoes must not replace (>) but append (>>) to that file.\n"
      "\n"
      "  /bin/echo -e \"pipe\\tOpen Files\\tlsof -P -p %d 2>&1\" >> ~/.toprc\n"
      "  /bin/echo -e \"file\\tNUMA Info\\t/proc/%d/numa_maps\" >> ~/.toprc\n"
      "  /bin/echo -e \"pipe\\tLog\\ttail -n200 /var/log/syslog | sort -Mr\" >> ~/.toprc\n"
      "\n"
      "If you don't know the location or name of the top rcfile, use the 'W' command\n"
      "and note those details.  After backing up the current rcfile, try issuing the\n"
      "above echoes exactly as shown, replacing '.toprc' as appropriate.  The safest\n"
      "approach would be to use copy then paste to avoid any typing mistakes.\n"
      "\n"
      "Finally, restart top to reveal what actual Inspect entries combined with this\n"
      "new command can offer.  The possibilities are endless, especially considering\n"
      "that 'pipe' type entries can include shell scripts too!\n"
      "\n"
      "For additional important information, please consult the top documentation.\n"
      "Then enhance top with your very own customized 'file' and 'pipe' entries.\n"
      "\n"
      "Enjoy!\n");
   Norm_nlstab[YINSP_demo05_txt] = _("the '=' key will eventually show the actual file read or command(s) excuted ...");
#endif
   Norm_nlstab[YINSP_failed_fmt] = _("Selection failed with: %s\n");
#ifndef INSP_OFFDEMO
   Norm_nlstab[YINSP_noents_txt] = _("to enable 'Y' press <Enter> then type 'W' and restart top");
#else
   Norm_nlstab[YINSP_noents_txt] = _("to enable 'Y' please consult the top man page (press Enter)");
#endif
   Norm_nlstab[YINSP_pidbad_fmt] = _("unable to inspect, pid %d not found");
   Norm_nlstab[YINSP_pidsee_fmt] = _("inspect at PID [defailt pid = %d]");
   Norm_nlstab[YINSP_rcfile_fmt] = _("could not parse rcfile inspect entry %d");
   Norm_nlstab[YINSP_status_fmt] = _("%s: %*d-%-*d lines, %*d-%*d columns, %lu bytes read");
   Norm_nlstab[YINSP_workin_txt] = _("patience please, working...");
}


        /*
         * This routine builds the nls table containing specially
         * formatted strings designed to fit within an 80x24 terminal. */
static void build_uniq_nlstab (void) {

/* Translation Notes ------------------------------------------------
   .  It is strongly recommend that the --no-wrap command line option
   .  be used with all supporting translation tools, when available.
   .
   .  The next several text groups contain special escape sequences
   .  representing values used to index a table at run-time.
   .
   .  Each such sequence consists of a tilde (~) followed by an ascii
   .  number in the range of '1' - '8'.  Examples are '~2', '~8', etc.
   .  These escape sequences must never themselves be translated but
   .  could be deleted.
   .
   .  If you remove these escape sequences (both tilde and number) it
   .  would make translation easier.  However, the ability to display
   .  colors and bold text at run-time will have been lost.
   .
   .  Additionally, each of these text groups was designed to display
   .  in a 80x24 terminal window.  Hopefully, any translations will
   .  adhere to that goal lest the translated text be truncated.
   .
   .  If you would like additional information regarding these strings,
   .  please see the prologue to the show_special function in the top.c
   .  source file.
   . */

   Uniq_nlstab[KEYS_helpbas_fmt] = _(""
      "Help for Interactive Commands~2 - %s\n"
      "Window ~1%s~6: ~1Cumulative mode ~3%s~2.  ~1System~6: ~1Delay ~3%.1f secs~2; ~1Secure mode ~3%s~2.\n"
      "\n"
      "  Z~5,~1B~5       Global: '~1Z~2' change color mappings; '~1B~2' disable/enable bold\n"
      "  l,t,m     Toggle Summaries: '~1l~2' load avg; '~1t~2' task/cpu stats; '~1m~2' mem info\n"
      "  1,I       Toggle SMP view: '~11~2' single/separate states; '~1I~2' Irix/Solaris mode\n"
      "  f,F,X     Fields: '~1f~2'/'~1F~2' add/remove/order/sort; '~1X~2' increase fixed-width\n"
      "\n"
      "  L,&,<,> . Locate: '~1L~2'/'~1&~2' find/again; Move sort column: '~1<~2'/'~1>~2' left/right\n"
      "  R,H,V,J . Toggle: '~1R~2' Sort; '~1H~2' Threads; '~1V~2' Forest view; '~1J~2' Num justify\n"
      "  c,i,S,j . Toggle: '~1c~2' Cmd name/line; '~1i~2' Idle; '~1S~2' Time; '~1j~2' Str justify\n"
      "  x~5,~1y~5     . Toggle highlights: '~1x~2' sort field; '~1y~2' running tasks\n"
      "  z~5,~1b~5     . Toggle: '~1z~2' color/mono; '~1b~2' bold/reverse (only if 'x' or 'y')\n"
      "  u,U     . Filter by: '~1u~2' effective user; '~1U~2' real, saved, file or effective user\n"
      "  n or #  . Set maximum tasks displayed\n"
      "  C,...   . Toggle scroll coordinates msg for: ~1up~2,~1down~2,~1left~2,right~2,~1home~2,~1end~2\n"
      "\n"
      "%s"
      "  W,Y       Write configuration file '~1W~2'; Inspect other output '~1Y~2'\n"
      "  q         Quit\n"
      "          ( commands shown with '.' require a ~1visible~2 task display ~1window~2 ) \n"
      "Press '~1h~2' or '~1?~2' for help with ~1Windows~2,\n"
      "any other key to continue ");

/* Translation Hint: As is true for the text above, the "keys" shown to the left and
   .                 also imbedded in the translatable text (along with escape seqs)
   .                 should never themselves be translated. */
   Uniq_nlstab[KEYS_helpext_fmt] = _(""
      "  k,r       Manipulate tasks: '~1k~2' kill; '~1r~2' renice\n"
      "  d or s    Set update interval\n");

   Uniq_nlstab[WINDOWS_help_fmt] = _(""
      "Help for Windows / Field Groups~2 - \"Current Window\" = ~1 %s ~6\n"
      "\n"
      ". Use multiple ~1windows~2, each with separate config opts (color,fields,sort,etc)\n"
      ". The 'current' window controls the ~1Summary Area~2 and responds to your ~1Commands~2\n"
      "  . that window's ~1task display~2 can be turned ~1Off~2 & ~1On~2, growing/shrinking others\n"
      "  . with ~1NO~2 task display, some commands will be ~1disabled~2 ('i','R','n','c', etc)\n"
      "    until a ~1different window~2 has been activated, making it the 'current' window\n"
      ". You ~1change~2 the 'current' window by: ~1 1~2) cycling forward/backward;~1 2~2) choosing\n"
      "  a specific field group; or~1 3~2) exiting the color mapping or fields screens\n"
      ". Commands ~1available anytime   -------------~2\n"
      "    A       . Alternate display mode toggle, show ~1Single~2 / ~1Multiple~2 windows\n"
      "    g       . Choose another field group and make it 'current', or change now\n"
      "              by selecting a number from: ~1 1~2 =%s;~1 2~2 =%s;~1 3~2 =%s; or~1 4~2 =%s\n"
      ". Commands ~1requiring~2 '~1A~2' mode~1  -------------~2\n"
      "    G       . Change the ~1Name~5 of the 'current' window/field group\n"
      " ~1*~4  a , w   . Cycle through all four windows:  '~1a~5' Forward; '~1w~5' Backward\n"
      " ~1*~4  - , _   . Show/Hide:  '~1-~5' ~1Current~2 window; '~1_~5' all ~1Visible~2/~1Invisible~2\n"
      "  The screen will be divided evenly between task displays.  But you can make\n"
      "  some ~1larger~2 or ~1smaller~2, using '~1n~2' and '~1i~2' commands.  Then later you could:\n"
      " ~1*~4  = , +   . Rebalance tasks:  '~1=~5' ~1Current~2 window; '~1+~5' ~1Every~2 window\n"
      "              (this also forces the ~1current~2 or ~1every~2 window to become visible)\n"
      "\n"
      "In '~1A~2' mode, '~1*~4' keys are your ~1essential~2 commands.  Please try the '~1a~2' and '~1w~2'\n"
      "commands plus the 'g' sub-commands NOW.  Press <Enter> to make 'Current' ");

/* Translation Notes ------------------------------------------------
   .  The following 'Help for color mapping' simulated screen should
   .  probably NOT be translated.  It is terribly hard to follow in
   .  this form and any translation could produce unpleasing results
   .  that are unlikely to parallel the running top program.
   .
   .  If you decide to proceed with translation, do the following
   .  lines only, taking care not to disturbe the tilde + number.
   .
   .  Simulated screen excerpt:
   .     --> "   Tasks:~3  64 ~2total,~3   2 ~3running,~3  62
   .     --> "   %%Cpu(s):~3  76.5 ~2user,~3  11.2 ~2system,~
   .     --> "   ~1 Nasty Message! ~4  -or-  ~1Input Prompt~5
   .
   .     --> "   available toggles: ~1B~2 =disable bold globa
   .     --> "       ~1z~2 =color/mono (~1%s~2), ~1b~2 =tasks
   .
   .     --> "Select ~1target~2 as upper case letter:\n"
   .     --> "   S~2 = Summary Data,~1  M~2 = Messages/Prompt
   .     --> "   H~2 = Column Heads,~1  T~2 = Task Informatio
   .     --> "Select ~1color~2 as number:\n"
   .     --> "   0~2 = black,~1  1~2 = red,    ~1  2~2 = gree
   .     --> "   4~2 = blue, ~1  5~2 = magenta,~1  6~2 = cyan
   . */
   Uniq_nlstab[COLOR_custom_fmt] = _(""
      "Help for color mapping~2 - %s\n"
      "current window: ~1%s~6\n"
      "\n"
      "   color - 04:25:44 up 8 days, 50 min,  7 users,  load average:\n"
      "   Tasks:~3  64 ~2total,~3   2 ~3running,~3  62 ~2sleeping,~3   0 ~2stopped,~3\n"
      "   %%Cpu(s):~3  76.5 ~2user,~3  11.2 ~2system,~3   0.0 ~2nice,~3  12.3 ~2idle~3\n"
      "   ~1 Nasty Message! ~4  -or-  ~1Input Prompt~5\n"
      "   ~1  PID TTY     PR  NI %%CPU    TIME+   VIRT SWAP S COMMAND    ~6\n"
      "   17284 ~8pts/2  ~7  8   0  0.0   0:00.75  1380    0 S /bin/bash   ~8\n"
      "   ~1 8601 pts/1    7 -10  0.4   0:00.03   916    0 R color -b -z~7\n"
      "   11005 ~8?      ~7  9   0  0.0   0:02.50  2852 1008 S amor -sessi~8\n"
      "   available toggles: ~1B~2 =disable bold globally (~1%s~2),\n"
      "       ~1z~2 =color/mono (~1%s~2), ~1b~2 =tasks \"bold\"/reverse (~1%s~2)\n"
      "\n"
      "Select ~1target~2 as upper case letter:\n"
      "   S~2 = Summary Data,~1  M~2 = Messages/Prompts,\n"
      "   H~2 = Column Heads,~1  T~2 = Task Information\n"
      "Select ~1color~2 as number:\n"
      "   0~2 = black,~1  1~2 = red,    ~1  2~2 = green,~1  3~2 = yellow,\n"
      "   4~2 = blue, ~1  5~2 = magenta,~1  6~2 = cyan, ~1  7~2 = white\n"
      "\n"
      "Selected: ~1target~2 ~1 %c ~4; ~1color~2 ~1 %d ~4\n"
      "   press 'q' to abort changes to window '~1%s~2'\n"
      "   press 'a' or 'w' to commit & change another, <Enter> to commit and end ");

   Uniq_nlstab[FIELD_header_fmt] = _(""
      "Fields Management~2 for window ~1%s~6, whose current sort field is ~1%s~2\n"
      "   Navigate with Up/Dn, Right selects for move then <Enter> or Left commits,\n"
      "   'd' or <Space> toggles display, 's' sets sort.  Use 'q' or <Esc> to end! ");

   Uniq_nlstab[STATE_line_1_fmt] = _("%s:~3"
      " %3u ~2total,~3 %3u ~2running,~3 %3u ~2sleeping,~3 %3u ~2stopped,~3 %3u ~2zombie~3\n");

   Uniq_nlstab[STATE_lin2x4_fmt] = _("%%%s~3"
      " %#5.1f  ~2user,~3 %#5.1f  ~2system,~3 %#5.1f  ~2nice,~3 %#5.1f  ~2idle~3\n");

   Uniq_nlstab[STATE_lin2x5_fmt] = _("%%%s~3"
      " %#5.1f  ~2user,~3 %#5.1f  ~2system,~3 %#5.1f  ~2nice,~3 %#5.1f  ~2idle,~3 %#5.1f  ~2IO-wait~3\n");

/* Translation Hint: Only the following abbreviations need be translated
   .                 us = user, sy = system, ni = nice, id = idle, wa = wait,
   .                 hi hardware interrupt, si = software interrupt */
   Uniq_nlstab[STATE_lin2x6_fmt] = _("%%%s~3"
      " %#5.1f ~2us,~3 %#5.1f ~2sy,~3 %#5.1f ~2ni,~3 %#5.1f ~2id,~3 %#5.1f ~2wa,~3 %#5.1f ~2hi,~3 %#5.1f ~2si~3\n");

/* Translation Hint: Only the following abbreviations need be translated
   .                 us = user, sy = system, ni = nice, id = idle, wa = wait,
   .                 hi hardware interrupt, si = software interrupt, st = steal time */
   Uniq_nlstab[STATE_lin2x7_fmt] = _("%%%s~3"
      "%#5.1f ~2us,~3%#5.1f ~2sy,~3%#5.1f ~2ni,~3%#5.1f ~2id,~3%#5.1f ~2wa,~3%#5.1f ~2hi,~3%#5.1f ~2si,~3%#5.1f ~2st~3\n");

/* Translation Hint: Only the following need be translated
   .                 abbreviations: Mem = physical memory/ram, Swap = the linux swap file
   .                 words:         total, used, free, buffers, cached */
   Uniq_nlstab[MEMORY_lines_fmt] = _(""
      "%s Mem: ~3 %8lu ~2total,~3 %8lu ~2used,~3 %8lu ~2free,~3 %8lu ~2buffers~3\n"
      "%s Swap:~3 %8lu ~2total,~3 %8lu ~2used,~3 %8lu ~2free,~3 %8lu ~2cached~3\n");

   Uniq_nlstab[INSP_hdrbase_fmt] = _(""
      "Inspection~2 Pause at:  pid ~1%d~6 running command ~1%s~6 as user ~1%s~6");

   Uniq_nlstab[INSP_hdrsels_fmt] = _(""
      "%s\n"
      "Use~2:  left/right then <Enter> to ~1select~5 an option; 'q' or <Esc> to ~1end~5 !\n"
      "Options~2: ~1%s\n");

   Uniq_nlstab[INSP_hdrview_fmt] = _(""
      "%s\n"
      "Use~2:  left/right/up/down/etc to ~1navigate~5 the output; 'L'/'&' to ~1locate~5/~1next~5.\n"
      "Or~2:   <Enter> to ~1select another~5; 'q' or <Esc> to ~1end~5 !\n");
}


        /*
         * This function must be called very early at startup, before
         * any other function call, and especially before any changes
         * have been made to the terminal if VALIDATE_NLS is defined!
         *
         * The gettext documentation suggests that alone among locale
         * variables LANGUAGE=ll_CC may be abbreviated as LANGUAGE=ll
         * to denote the language's main dialect.  Unfortunately this
         * does not appear to be true.  One must specify the complete
         * ll_CC.  Optionally, a '.UTF-8' or '.uft8' suffix, as shown
         * in the following examples, may also be included:
         *    export LANGUAGE=ll_CC          # minimal requirement
         *    export LANGUAGE=ll_CC.UTF-8    # optional convention
         *    export LANGUAGE=ll_CC.utf8     # ok, too
         *
         * Additionally, as suggested in the gettext documentation, a
         * user will also have to export an empty LC_ALL= to actually
         * enable any translations.
         */
void initialize_nls (void) {
#ifdef VALIDATE_NLS
   static const char *nls_err ="\t%s_nlstab[%d] == NULL\n";
   int i;

   setlocale (LC_ALL, "");
   bindtextdomain(PACKAGE, LOCALEDIR);
   textdomain(PACKAGE);

   memset(Head_nlstab, 0, sizeof(Head_nlstab));
   memset(Desc_nlstab, 0, sizeof(Desc_nlstab));
   build_two_nlstabs();
   for (i = 0; i < P_MAXPFLGS; i++) {
      if (!Head_nlstab[i]) {
         fprintf(stderr, nls_err, "Head", i);
         exit(1);
      }
      if (!Desc_nlstab[i]) {
         fprintf(stderr, nls_err, "Desc", i);
         exit(1);
      }
   }
   memset(Norm_nlstab, 0, sizeof(Norm_nlstab));
   build_norm_nlstab();
   for (i = 0; i < norm_MAX; i++)
      if (!Norm_nlstab[i]) {
         fprintf(stderr, nls_err, "Norm", i);
         exit(1);
      }
   memset(Uniq_nlstab, 0, sizeof(Uniq_nlstab));
   build_uniq_nlstab();
   for (i = 0; i < uniq_MAX; i++)
      if (!Uniq_nlstab[i]) {
         fprintf(stderr, nls_err, "Uniq", i);
         exit(1);
      }
 #ifndef INSP_OFFDEMO
   if (READMINSZ < strlen(N_txt(YINSP_demo04_txt)) +1) {
      fprintf(stderr
         , "\nAssertion Failed in %s (%s):\n"
            "\t'READMINSZ < strlen(N_txt(YINSP_demo04_txt)) + 1'\n"
            "READMINSZ must be at least %u !\n\n"
         , __FILE__,  __func__, (unsigned)strlen(N_txt(YINSP_demo04_txt)) + 1);
         exit(1);
   }
 #endif
#else
   setlocale (LC_ALL, "");
   bindtextdomain(PACKAGE, LOCALEDIR);
   textdomain(PACKAGE);

   build_two_nlstabs();
   build_norm_nlstab();
   build_uniq_nlstab();
#endif
}
