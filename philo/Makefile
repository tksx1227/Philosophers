BINDIR	:= bin
SRCDIR	:= src
OBJDIR	:= obj
INCDIR	:= include

FILES	:= main.c \
			parser.c \
			philo_actions.c \
			philo_actions2.c \
			philo_observer.c \
			philo_thread.c \
			philo_utils.c \
			utils.c
SRCS	:= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
DEPS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.d))

CC		:= cc
RM		:= rm -rf
NAME	:= philo
PHILO	:= $(BINDIR)/philo
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
LINKLIB	:= -pthread

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LINKLIB) $(addprefix -I, $(INCDIR)) -c $< -o $@

.PHONY: all
all: $(OBJDIR) $(BINDIR) $(PHILO)

.PHONY: $(NAME)
$(NAME): all

$(PHILO): $(OBJS)
	@echo "\033[32mGenerate binary file...\033[0m"
	$(CC) $(CFLAGS) $(LINKLIB) -o $@ $^

$(OBJDIR):
	@echo "\033[32mGenerate $(OBJDIR) directory...\033[0m"
	mkdir -p $@

$(BINDIR):
	@echo "\033[32mGenerate $(BINDIR) directory...\033[0m"
	mkdir -p $@

.PHONY: clean
clean:
	@echo "\033[31mRemove $(OBJDIR) directory...\033[0m"
	$(RM) $(OBJDIR)

.PHONY: fclean
fclean: clean
	@echo "\033[31mRemove $(BINDIR) directory...\033[0m"
	$(RM) $(BINDIR)

.PHONY: re
re: fclean all

-include $(DEPS)
