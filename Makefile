#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:07 by ciglesia          #+#    #+#              #
#    Updated: 2021/08/11 20:40:37 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	fdf

#****************** INC *******************#
# General
INC			=	./include/

# Lib
LIB			=	./lib/
LIBINC		=	$(LIB)/include/

LIBFT		=	$(LIB)/libft/
LIBMLX		=	$(LIB)/minilibx-linux/

INC_LIB		=	-L$(LIBFT) -lft -L$(LIBMLX) -lmlx -lXext -lX11 -lm -lbsd

INCLUDE		=	-O3 -I $(INC) -I $(LIBINC)

#***************** SRC ********************#

DIRSRC		=	./src/
DIRANA		=	$(DIRSRC)/analyze/
DIRCOM		=	$(DIRSRC)/compute/
DIRDIS		=	$(DIRSRC)/display/

SRC			=	main.c
ANALYZE		=	analyze.c
COMPUTE		=
DISPLAY		=	render.c

SRCS		=	$(SRC) $(ANALYZE) $(COMPUTE) $(DISPLAY)

#***************** DEPS ******************#

DIROBJ		=	./depo/

OAUX		=	$(SRCS:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

ifndef VERBOSE
.SILENT:
endif

CC			=	/usr/bin/clang
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e
BOLD		=	"\e[1m"
BLINK		=	 "\e[5m"
RED			=	 "\e[38;2;255;0;0m"
GREEN		=	 "\e[92m"
BLUE		=	 "\e[34m"
YELLOW		=	 "\e[33m"
E0M			=	 "\e[0m"

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				@printf $(GREEN)"Generating fdf objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRANA)/%.c
				@printf $(GREEN)"Generating fdf objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRCOM)/%.c
				@printf $(GREEN)"Generating fdf objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRDIS)/%.c
				@printf $(GREEN)"Generating fdf objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

#************************ MAIN COMPILATION *************************

$(NAME)	:		ftlib $(OBJS) compiled
				@$(CC)  $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) $(BOLD)$(GREEN)'> fdf Compiled'$(E0M)

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@(cd $(LIB) && $(MAKE) clean)
				@$(ECHO) $(BOLD)$(RED)'> fdf directory        cleaned'$(E0M)

all		:		$(NAME)

fclean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@($(RM) $(NAME))
				@(cd $(LIB) && $(MAKE) fclean)
				@$(ECHO) $(BOLD)$(RED)'> fdf directory        cleaned'$(E0M)
				@$(ECHO) $(BOLD)$(RED)'> Executable             removed'$(E0M)

re		:		fclean all

ftlib	:
				@(cd $(LIB) && $(MAKE))

apt		:
				@(cd $(LIB) && $(MAKE) apt)

compiled:
				./compiled

.PHONY	:		all clean fclean re ftlib apt compiled

-include $(DEPS)
