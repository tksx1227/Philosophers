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
	@echo "\e[32mGenerate binary file...\e[0m"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "\e[32mGenerate object files...\e[0m"
	$(CC) $(CFLAGS) $(addprefix -I, $(INCDIR)) -c $< -o $@

$(OBJDIR):
	@echo "\e[32mGenerate obj directory...\e[0m"
	mkdir -p $@

$(BINDIR):
	@echo "\e[32mGenerate bin directory...\e[0m"
	mkdir -p $@

run: $(NAME)
	@echo "\e[32mRun: $(PHILO)\e[0m"
	@$(PHILO)

clean:
	@echo "\e[31mRemove object directory...\e[0m"
	$(RM) $(OBJDIR)

fclean: clean
	@echo "\e[31mRemove binary directory...\e[0m"
	$(RM) $(BINDIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
