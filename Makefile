NAME = server cli
SERVER = server
CLI = cli
SHARED_INCLUDES = ./includes/
VPATH = ./libs/mongoose/ ./libs/cjson/ ./libs/sqlite3/ ./libs/libft/ ./source/server/ ./source/cli/ ./source/shared_utils/
LOGS_DIR = ./logs/
OBJECTS_DIR = ./objects/

SERVER_INCLUDES = ./source/server/
SERVER_SOURCE = server.c db.c server_utils.c shared_utils.c create_log.c routes.c mongoose.c cJSON.c sqlite3.c
SERVER_OBJECTS_DIR = ./objects/server/
SERVER_OBJECTS =  $(SERVER_SOURCE:%.c=$(SERVER_OBJECTS_DIR)%.o)

CLI_INCLUDES = ./source/cli/
CLI_SOURCE = cli.c shared_utils.c
CLI_OBJECTS_DIR = ./objects/cli/
CLI_OBJECTS = $(CLI_SOURCE:%.c=$(CLI_OBJECTS_DIR)%.o)

LIBFT_DIR = ./libs/libft/
LIBFT_INCLUDE = ./libs/libft/includes/
LIBFT = ./libs/libft/libft.a
MONGOOSE_INCLUDE = ./libs/mongoose/
SQLITE3_INCLUDE  = ./libs/sqlite3/
CJSON_INCLUDE = ./libs/cjson/

FLAGS = -g -lpthread -ldl -lm
CC = gcc

all: $(NAME)

$(NAME): $(LOGS_DIR) $(LIBFT)

$(LOGS_DIR):
	@mkdir -p logs

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(SERVER): $(SERVER_OBJECTS_DIR) $(SERVER_OBJECTS)
	@$(CC) $(SERVER_OBJECTS) $(FLAGS) $(LIBFT) -I$(SHARED_INCLUDES) -I$(SERVER_INCLUDES) -I$(MONGOOSE_INCLUDE) -I$(CJSON_INCLUDE) -I$(SQLITE3_INCLUDE) -I$(LIBFT_INCLUDE) -o $@

$(SERVER_OBJECTS_DIR)%.o: %.c
	@$(CC) -c $< $(FLAGS) -I$(SERVER_INCLUDES) -I$(SHARED_INCLUDES) -I$(MONGOOSE_INCLUDE) -I$(CJSON_INCLUDE) -I$(SQLITE3_INCLUDE) -I$(LIBFT_INCLUDE) -o $@

$(SERVER_OBJECTS_DIR):
	@mkdir -p objects/server

$(CLI): $(CLI_OBJECTS_DIR) $(CLI_OBJECTS)
	@$(CC) $(CLI_OBJECTS) $(LIBFT) -I$(SHARED_INCLUDES) -I$(CLI_INCLUDES) -I$(LIBFT_INCLUDE) -o $@

$(CLI_OBJECTS_DIR)%.o: %.c
	@$(CC) -c $< -I$(CLI_INCLUDES) -I$(SHARED_INCLUDES) -I$(LIBFT_INCLUDE) -o $@

$(CLI_OBJECTS_DIR):
	@mkdir -p objects/cli

clean:
	@rm -rf $(LOGS_DIR)
	@rm -rf $(OBJECTS_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all
