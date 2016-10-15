static string _score_file_name()
static string _log_file_name()
int hiscores_new_entry(const scorefile_entry &ne)
void logfile_new_entry(const scorefile_entry &ne)
static void _hiscores_print_entry(const scorefile_entry &se, int index, int format, t_printf pf)
void hiscores_print_all(int display_count, int format)
void hiscores_print_list(int display_count, int format, int newest_entry)
static void _add_hiscore_row(MenuScroller* scroller, scorefile_entry& se, int id)
static void _construct_hiscore_table(MenuScroller* scroller)
static void _show_morgue(scorefile_entry& se)
void show_hiscore_table()
static const char *_range_type_verb(const char *const aux)
string hiscores_format_single(const scorefile_entry &se)
static bool _hiscore_same_day(time_t t1, time_t t2)
static string _hiscore_date_string(time_t time)
static string _hiscore_newline_string()
string hiscores_format_single_long(const scorefile_entry &se, bool verbose)
	// BEGIN private functions
static FILE *_hs_open(const char *mode, const string &scores)
static void _hs_close(FILE *handle, const string &scores)
static bool _hs_read(FILE *scores, scorefile_entry &dest)
static int _val_char(char digit)
static time_t _parse_time(const string &st)
static void _hs_write(FILE *scores, scorefile_entry &se)
static const char *kill_method_names[] =
static const char *_kill_method_name(kill_method_type kmt)
static kill_method_type _str_to_kill_method(const string &s)
	// scorefile_entry
scorefile_entry::scorefile_entry(int dam, mid_t dsource, int dtype, const char *aux, bool death_cause_only, const char *dsource_name, time_t dt)
scorefile_entry::scorefile_entry()
scorefile_entry::scorefile_entry(const scorefile_entry &se)
scorefile_entry &scorefile_entry::operator = (const scorefile_entry &se)
void scorefile_entry::init_from(const scorefile_entry &se)
actor* scorefile_entry::killer() const
xlog_fields scorefile_entry::get_fields() const
bool scorefile_entry::parse(const string &line)
string scorefile_entry::raw_string() const
bool scorefile_entry::parse_scoreline(const string &line)
static const char* _short_branch_name(int branch)
enum old_job_type
static const char* _job_name(int job)
static const char* _job_abbrev(int job)
static int _job_by_name(const string& name)
enum old_species_type
static string _species_name(int race)
static const char* _species_abbrev(int race)
static int _species_by_name(const string& name)
void scorefile_entry::init_with_fields()
void scorefile_entry::set_base_xlog_fields() const
void scorefile_entry::set_score_fields() const
string scorefile_entry::make_oneline(const string &ml) const
string scorefile_entry::long_kill_message() const
string scorefile_entry::short_kill_message() const
static bool _strip_to(string &str, const char *infix)
void scorefile_entry::init_death_cause(int dam, mid_t dsrc, int dtype, const char *aux, const char *dsrc_name)
void scorefile_entry::reset()
static int _award_modified_experience()
void scorefile_entry::init(time_t dt)
string scorefile_entry::hiscore_line(death_desc_verbosity verbosity) const
string scorefile_entry::game_time(death_desc_verbosity verbosity) const
const char *scorefile_entry::damage_verb() const
string scorefile_entry::death_source_desc() const
string scorefile_entry::damage_string(bool terse) const
string scorefile_entry::strip_article_a(const string &s) const
string scorefile_entry::terse_missile_name() const
string scorefile_entry::terse_missile_cause() const
string scorefile_entry::terse_beam_cause() const
string scorefile_entry::terse_wild_magic() const
void scorefile_entry::fixup_char_name()
string scorefile_entry::single_cdesc() const
static string _append_sentence_delimiter(const string &sentence, const string &delimiter)
string scorefile_entry::character_description(death_desc_verbosity verbosity) const
string scorefile_entry::death_place(death_desc_verbosity verbosity) const
string scorefile_entry::death_description(death_desc_verbosity verbosity) const
	// xlog_fields
xlog_fields::xlog_fields() : fields(), fieldmap()
xlog_fields::xlog_fields(const string &line) : fields(), fieldmap()
static string _xlog_escape(const string &s)
static string _xlog_unescape(const string &s)
static string::size_type _xlog_next_separator(const string &s, string::size_type start)
static vector<string> _xlog_split_fields(const string &s)
void xlog_fields::init(const string &line)
void xlog_fields::add_field(const string &key, const char *format, ...)
string xlog_fields::str_field(const string &s) const
int xlog_fields::int_field(const string &s) const
void xlog_fields::map_fields() const
string xlog_fields::xlog_line() const
	// Milestones
void mark_milestone(const string &type, const string &milestone, const string &origin_level, time_t milestone_time)
string xlog_status_line()