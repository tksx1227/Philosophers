BINDIR	:= bin
SRCDIR	:= src
OBJDIR	:= obj
INCDIR	:= include

SRCS	:= main.c
OBJS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEPS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.d))

CC		:= cc
RM		:= rm -rf
NAME	:= philo
PHILO	:= $(BINDIR)/philo
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP

all: $(OBJDIR) $(BINDIR) $(PHILO)

$(NAME): all

$(PHILO): $(OBJS)
	@echo "\033[32mGenerate binary file...\033[0m"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "\033[32mGenerate object files...\033[0m"
	$(CC) $(CFLAGS) $(addprefix -I, $(INCDIR)) -c $< -o $@

$(OBJDIR):
	@echo "\033[32mGenerate obj directory...\033[0m"
	mkdir -p $@

$(BINDIR):
	@echo "\033[32mGenerate bin directory...\033[0m"
	mkdir -p $@

run: $(NAME)
	@echo "\033[32mRun: $(PHILO)\033[0m"
	@$(PHILO)

clean:
	@echo "\033[31mRemove object directory...\033[0m"
	$(RM) $(OBJDIR)

fclean: clean
	@echo "\033[31mRemove binary directory...\033[0m"
	$(RM) $(BINDIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
