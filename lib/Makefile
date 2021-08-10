#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 22:37:03 by ciglesia          #+#    #+#              #
#    Updated: 2021/08/10 19:10:10 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEPENDENCIES = Makefile libft/Makefile minilibx-linux/Makefile

ECHO		=	/bin/echo -e

.SUFFIXES:

ifndef VERBOSE
.SILENT:
endif

all:	$(DEPENDENCIES)
		@$(MAKE) -C libft/
		@$(MAKE) -C minilibx-linux/

clean:
		@$(MAKE) -C libft/ clean
		@$(MAKE) -C minilibx-linux/ clean

fclean:
		@$(MAKE) -C libft/ fclean
		@$(MAKE) -C minilibx-linux/ clean

re:
		@$(ECHO) "Recompiling libraries..."
		@$(MAKE) fclean
		@$(MAKE) all

apt:
		sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev

.PHONY: clean fclean all re
