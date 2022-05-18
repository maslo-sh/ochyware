#ifndef LOG_TAGS
#define LOG_TAGS

typedef enum log_tag{
    ERROR,
    INFO,
    PROMPT,
    SUCCESS,
    VIRUS
} log_tag_t;

typedef enum output_color{
    ERR_COLOR,
    SUCCESS_COLOR,
    PROMPT_COLOR,
    INFO_COLOR,
    VIRUS_COLOR
} output_color_t;

typedef struct log_conf {
    log_tag_t tag;
    output_color_t color;
} log_conf_t;

extern log_conf_t SUCCESS_CONF;

extern log_conf_t ERR_CONF;

extern log_conf_t PROMPT_CONF;

extern log_conf_t INFO_CONF;

extern log_conf_t VIRUS_CONF;
#endif