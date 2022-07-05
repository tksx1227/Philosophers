BINDIR	:= bin
SRCDIR	:= src
OBJDIR	:= obj
INCDIR	:= include

FILES	:= main.c
SRCS	:= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
DEPS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.d))

CC		:= cc
RM		:= rm -rf
NAME	:= philo_bonus
PHILO	:= $(BINDIR)/philo_bonus
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
LINKLIB	:= -pthread

ifdef DEV
	CFLAGS += -g -fsanitize=thread
endif

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

.PHONY: dev
dev:
	@$(MAKE) DEV=1

-include $(DEPS)
