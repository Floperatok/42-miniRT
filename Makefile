# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drenassi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 14:42:11 by drenassi          #+#    #+#              #
#    Updated: 2024/02/22 12:10:48 by drenassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################


NAME		= miniRT
CC 			= cc
CFLAGS		= -Wall -Werror -Wextra
DEBUG_FLAGS = -g3
MLXFLAGS	= -Imlx -lX11 -lXext
MATH_FLAGS	= -lm
AUTHOR		= drenassi
DATE		= 09/11/2023
NOVISU 		= 0 # 1 = no progress bar usefull when tty is not available

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

FILE_EXTENSION	= .c


MLX_PATH		= libs/minilibx-linux
MLX				= libs/minilibx.a

LIBFT_PATH		= libs/libft
LIBFT			= libs/libft.a

INCLUDE_PATH	= includes

SRCS_PATH		= src
SRCS			= utils/double/ft_atod.c \
				  utils/str/ft_strcmp.c \
				  utils/str/double_array_len.c \
				  utils/str/free_double_array.c \
				  utils/str/is_empty.c \
				  utils/str/print_error.c \
				  utils/maths/vectors.c \
				  utils/maths/vectors2.c \
				  utils/maths/intersections.c \
				  utils/maths/rotations.c \
				  utils/colors.c \
				  utils/print_data.c \
				  check_file/check_file.c \
				  check_file/check_double.c \
				  check_file/rgb.c \
				  check_file/coordinates.c \
				  check_file/identifier.c \
				  check_file/ambient_lightning.c \
				  check_file/camera.c \
				  check_file/light.c \
				  check_file/plane.c \
				  check_file/sphere.c \
				  check_file/cylinder.c \
				  init/create_data_array.c \
				  init/set_data.c \
				  init/window.c \
				  init/image.c \
				  init/ambient_light.c \
				  init/camera.c \
				  init/viewport.c \
				  init/light.c \
				  init/point.c \
				  init/sphere.c \
				  init/cylinder.c \
				  init/plane.c \
				  init/objects_list.c \
				  init/init_objects.c \
				  input/input_handling.c \
				  computations/raytracing.c \
				  computations/ray.c \
				  computations/ambient_lightning.c \
				  computations/light.c \
				  computations/reflection.c \
				  computations/intersections.c \
				  computations/sdf.c \
				  rendering/draw_pixels.c \
				  rendering/loading_display.c \
				  rendering/rendering.c

MAIN			= main.c

################################################################################
#                                  MAKEFILE  OBJS                              #
################################################################################

SHELL := /bin/bash

OBJS_PATH			= objs

OBJS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.o})
OBJ_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.o})

################################################################################
#                                 MAKEFILE LOGIC                               #
################################################################################

TITLE_COLOR	= \033[0;34m
COM_COLOR   = \033[0;36m
OBJ_COLOR   = \033[m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

COM_STRING   = "Compiled"

HASH	= 

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin) 
	RUN_CMD = script -q $@.log $1 > /dev/null; \
				RESULT=$$?
else ifeq ($(detected_OS),Linux)
	RUN_CMD = script -q -e -c "$(1)" $@.log > /dev/null; \
				RESULT=$$?; \
				sed -i '1d' $@.log; \
				sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
else
	RUN_CMD = $(1) 2> $@.log; \
				RESULT=$$?
endif

ifeq ($(shell git rev-parse HEAD &>/dev/null; echo $$?),0)
	AUTHOR	:= $(shell git log --format='%aN' | sort -u | awk '{printf "%s, ", $$0}' | rev | cut -c 3- | rev)
	DATE	:= $(shell git log -1 --date=format:"%Y/%m/%d %T" --format="%ad")
	HASH	:= $(shell git rev-parse --short HEAD)
endif

define run_and_test
printf "%b%-46b" "$(COM_COLOR)$(COM_STRING) " "$(OBJ_COLOR)$(@F)$(NO_COLOR)"; \
$(RUN_CMD); \
if [[ $$RESULT -ne 0 ]]; then \
	printf "%b\n" "$(ERROR_COLOR)[✖]$(NO_COLOR)"; \
	rm -rf .files_changed; \
	if [[ $(NOVISU) -eq 0 ]]; then \
		echo; \
	fi; \
elif [[ -s $@.log ]]; then \
	printf "%b\n" "$(WARN_COLOR)[⚠]$(NO_COLOR)"; \
else  \
	printf "%b\n" "$(OK_COLOR)[✓]$(NO_COLOR)"; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

define save_files_changed
	FILE_CPP=`echo $(SRCS) $(MAIN) $(LIBFT) $(MLX)`; \
	FILE_OBJ=`find objs -type f -name '*.o' 2>/dev/null | sed 's/objs\///'`; \
	FILE_LIB=`find . -maxdepth 1 -type f -name '*.a' 2>/dev/null | sed 's/.\///'`; \
	TO_COMPILE=`echo $$FILE_CPP | wc -w`; \
	for FILE in $$FILE_CPP; do \
		for OBJ in $$FILE_OBJ; do \
			if [[ $${FILE%$(FILE_EXTENSION)} = $${OBJ%.o} ]]; then \
				if [[ $(SRCS_PATH)/$$FILE -ot objs/$$OBJ ]]; then \
					RECOMPILE=0; \
					if [[ $$RECOMPILE -eq 0 ]]; then \
						((TO_COMPILE=$$TO_COMPILE-1)); \
					fi; \
				fi; \
			fi; \
		done; \
		for LIB in $$FILE_LIB; do \
			if [[ $${FILE%$(FILE_EXTENSION)} = $${LIB%.a} ]]; then \
				if [[ $(SRCS_PATH)/$$FILE -ot $$LIB ]]; then \
					RECOMPILE=0; \
					if [[ $$RECOMPILE -eq 0 ]]; then \
						((TO_COMPILE=$$TO_COMPILE-1)); \
					fi; \
				fi; \
			fi; \
		done; \
	done; \
	echo 0/$$TO_COMPILE > .files_changed
endef

define draw_bar
	FILE_TOTAL=`bash -c 'cat .files_changed | cut -d"/" -f2'`; \
	FILE_DONE=`bash -c 'cat .files_changed | cut -d"/" -f1'`; \
	if [[ $$FILE_TOTAL -eq 0 ]]; then \
		FILE_TOTAL=1; \
		FILE_DONE=1; \
	fi; \
	RES=`echo "scale=2; $$FILE_DONE/$$FILE_TOTAL*48" | bc`; \
	RES=`echo $${RES%%.*}`; \
	printf "$(OBJ_COLOR)[$(NO_COLOR)"; \
	i=0; \
	while [ $$i -lt 48 ]; do \
		if [[ $$i -lt $$RES ]]; then \
			printf "$(OK_COLOR)█$(NO_COLOR)"; \
		else \
			printf "$(COM_COLOR)▒$(NO_COLOR)"; \
		fi; \
		((i=$$i+1)); \
	done; \
	printf "$(OBJ_COLOR)]$(NO_COLOR)"; \
	printf " ($(COM_COLOR)$$FILE_DONE$(NO_COLOR)/$(COM_COLOR)$$FILE_TOTAL$(NO_COLOR))"; \
	printf " "; \
	((FILE_DONE=$$FILE_DONE+1)); \
	echo $$FILE_DONE/$$FILE_TOTAL > .files_changed;
endef

define display_progress_bar
	if [[ $(NOVISU) -eq 0 ]]; then \
		line=`bash -c 'oldstty=$$(stty -g); \
		stty raw -echo min 0; tput u7 > /dev/tty; IFS=";" \
		read -r -d R -a pos; stty $$oldstty; \
		row=$$(($${pos[0]:2} - 1)); echo $$row'`; \
		max_line=`tput lines`; \
		((max_line=$$max_line-2));\
		new_line=0; \
		tput sc; \
		i=0; \
		while [ $$i -lt 60 ]; do \
			printf " "; \
			((i=$$i+1)); \
		done; \
		tput rc; \
		if [[ $$line -gt $$max_line ]]; then \
			new_line=1; \
			echo ; \
		else \
			((line=$$line+1));\
		fi; \
		tput sc; \
		tput cup $$line; \
		$(draw_bar) \
		if [[ $$new_line -eq 1 ]]; then \
			((line=$$line-1));\
			tput cup $$line; \
		else \
			tput rc; \
		fi; \
	fi
endef

################################################################################
#                                 MAKEFILE RULES                               #
################################################################################

###################################### ALL #####################################
.PHONY:																		all
all: header setup $(NAME)
	@rm -rf .files_changed

#################################### HEADER ####################################
.PHONY:																		header
header:
	@printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	@printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	@printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	@printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	@tput cup init
	@printf "%b"
	@echo "                              _ _                            _ "
	@echo "                             | | |                          | |"
	@echo "              _ __  ___  __ _| | | ___ ___    __ _ _ __   __| |"
	@echo "             | '_ \/ __|/ _\` | | |/ _ / __|  / _\` | '_ \ / _\` |"
	@echo "             | | | \__ | (_| | | |  __\__ \ | (_| | | | | (_| |"
	@echo "             |_| |_|___/\__,_|_|_|\___|___/  \__,_|_|_|_|\__,_|"
	@echo "                     | |                            (_)        "
	@echo "                   __| |_ __ ___ _ __   __ _ ___ ___ _         "
	@echo "                  / _\` | '__/ _ | '_ \ / _\` / __/ __| |        "
	@echo "                 | (_| | | |  __| | | | (_| \__ \__ | |        "
	@echo "                  \__,_|_|  \___|_| |_|\__,_|___|___|_|        "
	@echo "                                                | |            "
	@echo "                   _ __  _ __ ___ ___  ___ _ __ | |_           "
	@echo "                  | '_ \| '__/ _ / __|/ _ | '_ \| __|          "
	@echo "                  | |_) | | |  __\__ |  __| | | | |_   _ _ _   "
	@echo "                  | .__/|_|  \___|___/\___|_| |_|\__| (_(_(_)  "
	@echo "                  | |                                          "
	@echo "                  |_|                                          "
	@printf "\n\n$(WARN_COLOR)"
	@echo "  __________________________________________________/\\\\\\\\\\\\\\\\\\______/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_        "
	@echo "   ________________________________________________/\\\\\\///////\\\\\\___\///////\\\\\\/////__       "
	@echo "    ______________________/\\\\\\________________/\\\\\\_\/\\\\\\_____\/\\\\\\_________\/\\\\\\_______      "
	@echo "     ____/\\\\\\\\\\__/\\\\\\\\\\___\///___/\\\\/\\\\\\\\\\\\___\///__\/\\\\\\\\\\\\\\\\\\\\\\/__________\/\\\\\\_______     "
	@echo "      __/\\\\\\///\\\\\\\\\\///\\\\\\__/\\\\\\_\/\\\\\\////\\\\\\___/\\\\\\_\/\\\\\\//////\\\\\\__________\/\\\\\\_______    "
	@echo "       _\/\\\\\\_\//\\\\\\__\/\\\\\\_\/\\\\\\_\/\\\\\\__\//\\\\\\_\/\\\\\\_\/\\\\\\____\//\\\\\\_________\/\\\\\\_______   "
	@echo "        _\/\\\\\\__\/\\\\\\__\/\\\\\\_\/\\\\\\_\/\\\\\\___\/\\\\\\_\/\\\\\\_\/\\\\\\_____\//\\\\\\________\/\\\\\\_______  "
	@echo "         _\/\\\\\\__\/\\\\\\__\/\\\\\\_\/\\\\\\_\/\\\\\\___\/\\\\\\_\/\\\\\\_\/\\\\\\______\//\\\\\\_______\/\\\\\\_______ "
	@echo "          _\///___\///___\///__\///__\///____\///__\///__\///________\///________\///________"
	@echo " "
	@echo
ifneq ($(HASH),)
	@printf "%b" "$(WARN_COLOR)Name:   $(NO_COLOR)$(NAME)@$(HASH)\n"
else
	@printf "%b" "$(WARN_COLOR)Name:   $(NO_COLOR)$(NAME)\n"
endif
	@printf "%b" "$(WARN_COLOR)Author: $(NO_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(WARN_COLOR)Date:   $(NO_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(WARN_COLOR)CC:     $(NO_COLOR)$(CC)\n\033[m"
	@printf "%b" "$(WARN_COLOR)Flags:  $(NO_COLOR)$(CFLAGS)\n\033[m"
	@echo

##################################### SETUP ####################################
.PHONY:																		setup
setup:
			@$(call save_files_changed)

################################## NAME'S RULE #################################
$(NAME):	${OBJS} ${OBJ_MAIN} ${LIBFT} ${MLX}
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN} ${LIBFT} ${MLX} $(MLXFLAGS) $(MATH_FLAGS))
			@printf "\33[2K\r\n"

################################# OBJECTS' RULE ################################
$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%$(FILE_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@ -I$(INCLUDE_PATH))

#################################### LIBFT #####################################
$(LIBFT):
			@$(call display_progress_bar)
			@make -sC $(LIBFT_PATH)
			@$(call run_and_test, mv $(LIBFT_PATH)/libft.a $@)

################################### MINILIBX ###################################
$(MLX):
			@$(call display_progress_bar)
			@make -sC $(MLX_PATH)
			@$(call run_and_test, mv $(MLX_PATH)/libmlx.a $@)

##################################### CLEAN ####################################
.PHONY:																		clean
clean:		header
			@make clean -sC $(LIBFT_PATH)
			@make clean -sC $(MLX_PATH)
			@rm -rf objs $(LIBFT) $(MLX)
			@printf "%-56b%b" "$(COM_COLOR)clean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

##################################### FCLEAN ####################################
.PHONY:																		fclean
fclean:		header clean
			@rm -rf $(NAME)
			@printf "%-56b%b" "$(COM_COLOR)fclean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

####################################### RE ######################################
.PHONY:																		re
re:			fclean all