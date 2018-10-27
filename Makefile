ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

####################################_COLOR_#####################################
GREEN = \033[38;5;10m
GREY = \033[38;5;60m
RED = \033[38;5;9m
END = \033[0m
##################################_COMPILATION_#################################
NAME = libft_malloc_$(HOSTTYPE).so
CC = clang
FLAG = -Weverything -g
FLAG = -Wall -Wextra -Werror -g
# LFT = ./libft/libft.a
SRCS =	malloc.c\
		ft_putnbr.c\
		ft_putstr.c\
		free.c\
		ft_itoa_base.c\
		ft_strlen.c\
		realloc.c\
		ft_memcpy.c\
		show_alloc_mem.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -I ./include \
          -I ./libft
###########################_RELINK_MODIFY_.h####################################
RELINK = ./include/malloc.h
################################################################################

    # @make -j8 -s -C ./libft/

all: $(NAME)

$(NAME): $(OBJS)
	@rm -rf libft_malloc.so $(NAME)
	@ln -s $(NAME) libft_malloc.so
	@$(CC) $(FLAG) $(OBJS) -shared -o $(NAME)
	@printf "✅  Compilation done.\n"

%.o : %.c $(RELINK)
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	@$(CC) -c $(FLAG) $< -o $@ $(INCLUDE)

clean:
	@printf "                                                               \r"
	@printf "✅  all .o deleted\n"
	@rm -f $(OBJS)
	@make -s clean -C ./libft/

fclean:
	@printf "                                                               \r"
	@printf "✅  libft.a, all .o and malloc deleted\n"
	@rm -f $(NAME) $(OBJS)
	@rm -rf libft_malloc.so $(NAME)
	@make -s fclean -C ./libft/

re: fclean all