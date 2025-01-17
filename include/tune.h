/** @file tune.h
 *
 * Header declaring the functions that support the \@tune function and
 * dealing with tunable configuration parameters.
 *
 * This file is part of Fuzzball MUCK.  Please see LICENSE.md for details.
 */

#ifndef TUNE_H
#define TUNE_H

#include <stdbool.h>
#include <stdio.h>

#include "array.h"
#include "db.h"

#define TUNESET_SUCCESS         0   /**< success                  */
#define TUNESET_SUCCESS_DEFAULT 5   /**< success, set to default  */
#define TUNESET_UNKNOWN         1   /**< unrecognized sysparm     */
#define TUNESET_SYNTAX          2   /**< bad value syntax         */
#define TUNESET_BADVAL          3   /**< bad value                */
#define TUNESET_DENIED          4   /**< mucker level too low     */

/* Tunable defaults management */

/**
 * Tunable parameter names must not start with TP_FLAG_DEFAULT or they won't
 * be saved.
 */
#define TP_FLAG_DEFAULT '%'

/** True if parameter starts with default flag, otherwise false */
#define TP_HAS_FLAG_DEFAULT(param) (param != NULL && param[0] == TP_FLAG_DEFAULT)

/** If specified, remove the reset to default flag by incrementing past it */
#define TP_CLEAR_FLAG_DEFAULT(param) if (TP_HAS_FLAG_DEFAULT(param)) { param++; }

/**
 * Potential tune value types
 */
union tuneval {
    const char *s; /**< string   */
    int t;         /**< timespan */
    int n;         /**< integer  */
    dbref d;       /**< dbref    */
    bool b;        /**< boolean  */
};

/**
 * The potential tune value types, as pointers
 */
union tuneval_ptr {
    const char **s; /**< string   */
    int *t;         /**< timespan */
    int *n;         /**< integer  */
    dbref *d;       /**< dbref    */
    bool *b;        /**< boolean  */
};

/**
 * An entry in the tune definition table
 */
struct tune_entry {
    const char *name;             /**< Parameter name           */
    const char *label;            /**< Parameter label          */
    const char *group;            /**< Configuration group      */
    const char *module;           /**< Associated module        */
    int type;                     /**< Parameter type           */
    union tuneval defaultval;     /**< Default value            */	
    union tuneval_ptr currentval; /**< Current value            */
    int readmlev;                 /**< MUCKER level to read     */
    int writemlev;                /**< MUCKER level to write    */
    bool isdefault;               /**< Is set to default value? */
    bool isnullable;              /**< Can be null? (str-only)  */
    int objecttype;               /**< Type (dbref-only)        */
};

/* These externs are defined in tunelist.h
 *
 * They contain the values associated with each tune variable, as a short
 * cut for C code that wants quick and easy access to the variables.
 *
 * This is the case for all these similar tp_ named externs in this file,
 * so they will not be individually documented.
 */
extern bool        tp_7bit_other_names;         /**< Tune variable */
extern bool        tp_7bit_thing_names;         /**< Tune variable */
extern int         tp_addpennies_muf_mlev;      /**< Tune variable */
extern int         tp_aging_time;               /**< Tune variable */
extern bool        tp_allow_listeners;          /**< Tune variable */
extern bool        tp_allow_listeners_env;      /**< Tune variable */
extern bool        tp_allow_listeners_obj;      /**< Tune variable */
extern bool        tp_allow_zombies;            /**< Tune variable */
extern bool        tp_autolink_actions;         /**< Tune variable */
extern const char *tp_autolook_cmd;             /**< Tune variable */
extern int         tp_clean_interval;           /**< Tune variable */
extern int         tp_cmd_log_threshold_msec;   /**< Tune variable */
extern bool        tp_cmd_only_overrides;       /**< Tune variable */
extern int         tp_command_burst_size;       /**< Tune variable */
extern int         tp_command_time_msec;        /**< Tune variable */
extern int         tp_commands_per_time;        /**< Tune variable */
extern bool        tp_compatible_priorities;    /**< Tune variable */
extern const char *tp_connect_fail_mesg;        /**< Tune variable */
extern bool        tp_consistent_lock_source;   /**< Tune variable */
extern const char *tp_cpennies;                 /**< Tune variable */
extern const char *tp_cpenny;                   /**< Tune variable */
extern const char *tp_create_fail_mesg;         /**< Tune variable */
extern bool        tp_dark_sleepers;            /**< Tune variable */
extern bool        tp_dbdump_warning;           /**< Tune variable */
extern dbref       tp_default_room_parent;      /**< Tune variable */
extern const char *tp_description_default;      /**< Tune variable */
extern bool        tp_diskbase_propvals;        /**< Tune variable */
extern bool        tp_do_mpi_parsing;           /**< Tune variable */
extern bool        tp_do_welcome_parsing;       /**< Tune variable */
extern int         tp_dump_interval;            /**< Tune variable */
extern int         tp_dump_warntime;            /**< Tune variable */
extern const char *tp_dumpdone_mesg;            /**< Tune variable */
extern bool        tp_dumpdone_warning;         /**< Tune variable */
extern const char *tp_dumping_mesg;             /**< Tune variable */
extern const char *tp_dumpwarn_mesg;            /**< Tune variable */
extern bool        tp_enable_home;              /**< Tune variable */
extern bool        tp_enable_prefix;            /**< Tune variable */
extern int         tp_exit_cost;                /**< Tune variable */
extern bool        tp_exit_darking;             /**< Tune variable */
extern bool        tp_expanded_debug_trace;     /**< Tune variable */
extern const char *tp_file_connection_help;     /**< Tune variable */
extern const char *tp_file_credits;             /**< Tune variable */
extern const char *tp_file_editor_help;         /**< Tune variable */
extern const char *tp_file_help;                /**< Tune variable */
extern const char *tp_file_help_dir;            /**< Tune variable */
extern const char *tp_file_info_dir;            /**< Tune variable */
extern const char *tp_file_log_cmd_times;       /**< Tune variable */
extern const char *tp_file_log_commands;        /**< Tune variable */
extern const char *tp_file_log_gripes;          /**< Tune variable */
extern const char *tp_file_log_malloc;          /**< Tune variable */
extern const char *tp_file_log_muf_errors;      /**< Tune variable */
extern const char *tp_file_log_programs;        /**< Tune variable */
extern const char *tp_file_log_sanfix;          /**< Tune variable */
extern const char *tp_file_log_sanity;          /**< Tune variable */
extern const char *tp_file_log_status;          /**< Tune variable */
extern const char *tp_file_log_stderr;          /**< Tune variable */
extern const char *tp_file_log_stdout;          /**< Tune variable */
extern const char *tp_file_log_user;            /**< Tune variable */
extern const char *tp_file_man;                 /**< Tune variable */
extern const char *tp_file_man_dir;             /**< Tune variable */
extern const char *tp_file_motd;                /**< Tune variable */
extern const char *tp_file_mpihelp;             /**< Tune variable */
extern const char *tp_file_mpihelp_dir;         /**< Tune variable */
extern const char *tp_file_news;                /**< Tune variable */
extern const char *tp_file_news_dir;            /**< Tune variable */
extern const char *tp_file_welcome_screen;      /**< Tune variable */
extern bool        tp_force_mlev1_name_notify;  /**< Tune variable */
extern int         tp_free_frames_pool;         /**< Tune variable */
extern const char *tp_gender_prop;              /**< Tune variable */
extern const char *tp_huh_mesg;                 /**< Tune variable */
extern const char *tp_idle_boot_mesg;           /**< Tune variable */
extern bool        tp_idle_ping_enable;         /**< Tune variable */
extern int         tp_idle_ping_time;           /**< Tune variable */
extern bool        tp_idleboot;                 /**< Tune variable */
extern bool        tp_ieee_bounds_handling;     /**< Tune variable */
extern bool        tp_ignore_bidirectional;     /**< Tune variable */
extern bool        tp_ignore_support;           /**< Tune variable */
extern int         tp_instr_slice;              /**< Tune variable */
extern const char *tp_leave_mesg;               /**< Tune variable */
extern int         tp_link_cost;                /**< Tune variable */
extern int         tp_listen_mlev;              /**< Tune variable */
extern bool        tp_lock_envcheck;            /**< Tune variable */
extern bool        tp_log_commands;             /**< Tune variable */
extern bool        tp_log_failed_commands;      /**< Tune variable */
extern bool        tp_log_interactive;          /**< Tune variable */
extern bool        tp_log_programs;             /**< Tune variable */
extern int         tp_lookup_cost;              /**< Tune variable */
extern dbref       tp_lost_and_found;           /**< Tune variable */
extern bool        tp_m3_huh;                   /**< Tune variable */
extern int         tp_max_force_level;          /**< Tune variable */
extern int         tp_max_instr_count;          /**< Tune variable */
extern int         tp_max_interp_recursion;     /**< Tune variable */
extern int         tp_max_loaded_objs;          /**< Tune variable */
extern int         tp_max_ml4_nested_interp_loop_count; /**< Tune variable */
extern int         tp_max_ml4_preempt_count;    /**< Tune variable */
extern int         tp_max_nested_interp_loop_count; /**< Tune variable */
extern int         tp_max_object_endowment;     /**< Tune variable */
extern int         tp_max_output;               /**< Tune variable */
extern int         tp_max_pennies;              /**< Tune variable */
extern int         tp_max_plyr_processes;       /**< Tune variable */
extern int         tp_max_process_limit;        /**< Tune variable */
extern int         tp_max_propfetch;            /**< Tune variable */
extern int         tp_maxidle;                  /**< Tune variable */
extern int         tp_mcp_muf_mlev;             /**< Tune variable */
extern int         tp_movepennies_muf_mlev;     /**< Tune variable */
extern bool        tp_mpi_continue_after_logout;    /**< Tune variable */
extern int         tp_mpi_max_commands;         /**< Tune variable */
extern const char *tp_muckname;                 /**< Tune variable */
extern bool        tp_muf_comments_strict;      /**< Tune variable */
extern const char *tp_new_program_flags;        /**< Tune variable */
extern int         tp_object_cost;              /**< Tune variable */
extern bool        tp_optimize_muf;             /**< Tune variable */
extern int         tp_pause_min;                /**< Tune variable */
extern const char *tp_pcreate_flags;            /**< Tune variable */
extern const char *tp_pennies;                  /**< Tune variable */
extern int         tp_pennies_muf_mlev;         /**< Tune variable */
extern const char *tp_penny;                    /**< Tune variable */
extern int         tp_penny_rate;               /**< Tune variable */
extern bool        tp_periodic_program_purge;   /**< Tune variable */
extern int         tp_player_name_limit;        /**< Tune variable */
extern dbref       tp_player_start;             /**< Tune variable */
extern bool        tp_playermax;                /**< Tune variable */
extern const char *tp_playermax_bootmesg;       /**< Tune variable */
extern int         tp_playermax_limit;          /**< Tune variable */
extern const char *tp_playermax_warnmesg;       /**< Tune variable */
extern bool        tp_pname_history_reporting;  /**< Tune variable */
extern int         tp_pname_history_threshold;  /**< Tune variable */
extern int         tp_process_timer_limit;      /**< Tune variable */
extern bool        tp_quiet_moves;              /**< Tune variable */
extern bool        tp_realms_control;           /**< Tune variable */
extern bool        tp_recognize_null_command;   /**< Tune variable */
extern const char *tp_register_mesg;            /**< Tune variable */
extern bool        tp_registration;             /**< Tune variable */
extern const char *tp_reserved_names;           /**< Tune variable */
extern const char *tp_reserved_player_names;    /**< Tune variable */
extern int         tp_room_cost;                /**< Tune variable */
extern bool        tp_secure_teleport;          /**< Tune variable */
extern bool        tp_secure_thing_movement;    /**< Tune variable */
extern bool        tp_secure_who;               /**< Tune variable */
extern bool        tp_server_cipher_preference; /**< Tune variable */
extern const char *tp_smtp_server;              /**> Described below */
extern const char *tp_smtp_port;                /**> Described below */
extern int         tp_smtp_ssl_type;            /**> Described below */
extern bool        tp_smtp_no_verify_cert;      /**> Described below */
extern int         tp_smtp_auth_type;           /**> Described below */
extern const char *tp_smtp_user;                /**> Described below */
extern const char *tp_smtp_password;            /**> Described below */
extern const char *tp_smtp_from_name;           /**> Described below */
extern const char *tp_smtp_from_email;          /**> Described below */
extern bool        tp_ssl_auto_reload_certs;    /**< Tune variable */
extern const char *tp_ssl_cert_file;            /**< Tune variable */
extern const char *tp_ssl_cipher_preference_list;   /**< Tune variable */
extern const char *tp_ssl_key_file;             /**< Tune variable */
extern const char *tp_ssl_keyfile_passwd;       /**< Tune variable */
extern const char *tp_ssl_min_protocol_version; /**< Tune variable */
extern int         tp_start_pennies;            /**< Tune variable */
extern bool        tp_starttls_allow;           /**< Tune variable */
extern bool        tp_strict_god_priv;          /**< Tune variable */
extern bool        tp_tab_input_replaced_with_space;    /**< Tune variable */
extern bool        tp_teleport_to_player;       /**< Tune variable */
extern bool        tp_thing_darking;            /**< Tune variable */
extern dbref       tp_toad_default_recipient;   /**< Tune variable */
extern bool        tp_toad_recycle;             /**< Tune variable */
extern bool        tp_use_hostnames;            /**< Tune variable */
extern int         tp_userlog_mlev;             /**< Tune variable */
extern dbref       tp_welcome_mpi_what;         /**< Tune variable */
extern dbref       tp_welcome_mpi_who;          /**< Tune variable */
extern bool        tp_who_hides_dark;           /**< Tune variable */
extern bool        tp_wiz_vehicles;             /**< Tune variable */

/**
 * @var tune_list
 *      This is the master list of tune list parameters which
 *      is defined in tunelist.h.
 */
extern struct tune_entry tune_list[];

/**
 * This takes an object and a string of flags, and sets them on the object
 *
 * The tunestr can have the following characters in it.  Each corresponds
 * to a flag.  Unknown flags are ignored.  '0' and 'W' cannot be set and
 * will be ignored.
 *
 * 1 2 3 A B C D G H J K L M O Q S V X Y Z
 *
 * Each corresponds to the first letter of the flag in question, with the
 * numbers being MUCKER levels.
 *
 * @param obj the object to set flags on
 * @param tunestr the string of flags
 */
void set_flags_from_tunestr(dbref obj, const char *tunestr);

/**
 * Count all available tune parameters.
 *
 * This is complicated by the fact that different parameter types are in
 * different arrays.
 *
 * @return integer number of tune paramters.
 */
int tune_count_parms(void);

/**
 * Free all tune parameters
 *
 * This will probably render the MUCK unstable if casually used; it is
 * for the MUCK shutdown process and is, in fact, one the last cleanups
 * called.
 */
void tune_freeparms(void);

/**
 * Get the string value of a given parameter
 *
 * The 'name' must match a parameter value, case insensitive.  If
 * it does not match a null string is returned.  If 'name' has
 * the default value prefix, that prefix is removed first.
 *
 * mlev is the player's MUCKER level for security checking.  If
 * security check fails, an empty string is returned.
 *
 * The string is in a static buffer, so this is not thread safe
 * and you must copy it if you want to ensure it doesn't mutate
 * out from under you.
 *
 * DBREFs will be prefixed with #, and booleans will return as "yes"
 * or "no".  Time will be a number in seconds.
 *
 * @param name the name of the parameter
 * @param mlev the MUCKER level of the calling player.
 * @return string as specified above.
 */
const char *tune_get_parmstring(const char *name, int mlev);

/**
 * Load default parameters into the global tune structures.
 *
 * This initializes all the global tune structures with default
 * values, marking each as isdefault=1 in the process.  If there
 * is an existing string value in a string tune setting, it will be
 * free'd (if not isdefault)
 *
 * This is a pretty destructive call.
 */
void tune_load_parms_defaults(void);

/**
 * Load tune params from a file.
 *
 * This loads the parameters from a file in the format written
 * by tune_save_parms_to_file.  It ignores lines that start with a #
 * mark.
 *
 * @see tune_save_parms_to_file
 * @see tune_setparm
 *
 * It will read up to 'cnt' number of lines, or all lines in the file if
 * cnt is a negative number.
 *
 * Player may either be NOTHING, or a player that will receive notifications.
 * The tune settings are done with MLEV_GOD no matter what MUCKER level
 * 'player' actually has.  If player is NOTHING, the process is silent.
 *
 * @param f the file handle to read from
 * @param player The player who will receive notifications, or NOTHING
 * @param cnt the count of lines to read or -1 to read all lines.
 */
void tune_load_parms_from_file(FILE * f, dbref player, int cnt);

/**
 * Creates a MUF PACKED (sequential) array from the tune parameters.
 *
 * Takes an optional pattern which is used a name search; "" matches
 * everything.
 *
 * @see equalstr
 *
 * mlevel is the MUCKER level of the person doing the call for
 * permission checking.  Pinned is sent directly to new_array_packed
 *
 * @see new_array_packed
 *
 * The resulting array is an array of dictionaries.  The dictionaries
 * vary slightly in structure based on the "type" of tune data.  In
 * common, they have the following fields:
 *
 * type - boolean, timespan, integer, dbref, string
 * group - the tune group this parameter belongs to
 * name - the name of the parameter
 * value - the value of the parameter
 * mlev - the MUCKER level required to read this parameter.
 * readmlev - the same as mlev
 * writemlev - the MUCKER level required to write this paramter.
 * label - some label text to explain the parameter
 * default - the default value
 * active - if this tune parameter is 'active' or applies to the MUCK
 * nullable - is this field able to be null?
 *
 * It may additionally have 'objtype', for type == dbref, which will
 * be 'any', 'player', 'thing', 'room', 'exit', 'program', 'garbage',
 * or 'unknown'
 *
 * @param pattern the pattern to search for
 * @param mlev the MUCKER level of the calling player
 * @param pinned pin the array?
 * @return a packed stk_array type - you are responsible to free this memory
 */
stk_array *tune_parms_array(const char *pattern, int mlev, int pinned);

/**
 * Save tune parameters to a file
 *
 * Some notes on parameter saving:
 *
 * Comment out default values saved to the output.  This allows distinguishing
 * between available parameters and customized parameters while still creating
 * a list of new parameters in fresh or updated databases.
 *
 * If value is specified, save it as normal.  It won't be marked as default
 * again until it's removed from the database (including commenting it out).
 *
 * Example:
 * > Custom
 * ssl_min_protocol_version=TLSv1.2
 * > Default
 * %ssl_min_protocol_version=None
 *
 * @param f the file handle to write to
 */
void tune_save_parms_to_file(FILE * f);

/**
 * Sets a tune parameter and handles all the intricaties therein
 *
 * For a given player 'player' with MUCKER level 'mlev', it will set
 * parameter 'parmname' to 'val', doing all necessary parsing.
 *
 * This will return one of the following integer constants:
 *
 * TUNESET_DENIED - permission denied
 * TUNESET_SUCCESS - success
 * TUNESET_SUCCESS_DEFAULT - successfully reset to default
 * TUNESET_UNKNOWN - unknown parmname
 * TUNESET_BADVAL - bad (invalid) value for parameter
 * TUNESET_SYNTAX - syntax error for val
 *
 * @param player the player doing the call
 * @param parmname the parameter to set
 * @param val the value to set the parameter to
 * @param security the MUCKER level of the player doing the call
 * @return integer result, as described above.
 */
int tune_setparm(dbref player, const char *parmname, const char *val,
                 int security);

#endif /* !TUNE_H */
