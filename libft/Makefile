##========== SOURCES ==========##

SRC = ft_arena.c \
      ft_complex_math.c \
      ft_isascii.c \
      ft_memcmp.c \
      ft_printf_special_handlers_p1.c \
      ft_putnbr_fd.c \
      ft_strdup.c \
      ft_strlcpy.c \
      ft_strprefix.c \
      ft_tolower.c \
      ft_atoi.c \
      ft_count.c \
      ft_isdigit.c \
      ft_isspace.c \
      ft_memcpy.c \
      ft_printf_special_handlers_p2.c \
      ft_putstr_fd.c \
      ft_strlen.c \
      ft_strrchr.c \
      ft_toupper.c \
      ft_bzero.c \
      ft_free.c \
      ft_isprint.c \
      ft_memmove.c \
      ft_printf_specials.c \
      ft_rand.c \
      ft_striteri.c \
      ft_strmapi.c \
      ft_strsufix.c \
      ft_calloc.c \
      ft_isalnum.c \
      ft_itoa.c \
      ft_memset.c \
      ft_putchar_fd.c \
      ft_split.c \
      ft_realloc.c \
      ft_strjoin.c \
      ft_strncmp.c \
      ft_strtrim.c \
      ft_complex.c \
      ft_isalpha.c \
      ft_memchr.c \
      ft_printf.c \
      ft_putendl_fd.c \
      ft_strchr.c \
      ft_strlcat.c \
      ft_strnstr.c \
      ft_substr.c \
      ft_llist_node_create.c \
      ft_llist_node_destroy.c \
      ft_llist_create.c \
      ft_llist_destroy.c \
      ft_llist_push.c \
      ft_llist_pop.c \
      ft_llist_append.c \
      ft_llist_truncate.c \
      ft_llist_get.c \
      strings/dstring.c \
      strings/dstring_char.c \
      strings/dstring_charp_manip.c \
      strings/dstring_conv1.c \
      strings/dstring_conv2.c \
      strings/dstring_conv3.c \
      strings/dstring_conv4.c \
      strings/dstring_conv5.c \
      strings/dstring_conv6.c \
      strings/dstring_conv7.c \
      strings/dstring_equals.c \
      strings/dstring_new.c \
      strings/dstring_split.c \
      strings/dstring_trim_utils.c \

MAIN = ft_free.c

##========== NAMES ==========##

NAME = libft.a
SRCS_DIR = ./
OBJS_DIR = ./OBJ/

##========== OBJECTS ==========##

OBJS := $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
MAIN_OBJ = $(addprefix $(OBJS_DIR),$(MAIN:.c=.o))

##========== COLORS ==========##

BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== COMPILATOR ==========##

CC = cc
LD = ar

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror -fPIE
LDFLAGS = $(LIBS) rcs 
LIBS = 

##========== MODES ==========##

TIMER = 0.01

ifdef DEBUG
	CFLAGS += -g #-fsanitize=address #(address, memory, thread)
	DEBUG_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all : $(CLEAR) $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MAIN_OBJ)
	@$(LD) $(LDFLAGS) $(NAME) $(MAIN_OBJ) $(OBJS)
	@echo "$(GREEN)-= $(NAME) compiled =-$(BASE_COLOR)"

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -rf $(NAME)
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
ifndef NOPRINT
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)Compiling $(NAME)$(BASE_COLOR)"
	@echo "╔==============================================╗"
	@echo -n "║$(GREEN)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n "▓"; \
		done
	@for i in $$(seq 1 $$(expr 45 - $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n " "; \
		done
	@echo "$(BASE_COLOR)║"
	@echo "╚==============================================╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
endif
	@mkdir -p $(dir $@)
ifdef NOPRINT
	@$(CC) $(CFLAGS) -c $< -o $@
else
	$(CC) $(CFLAGS) -c $< -o $@
endif

.PHONY : all bonus clean fclean re
