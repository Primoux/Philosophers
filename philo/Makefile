# GENERAL SETTINGS ====================================================================
NAME	= philo

# DIRECTORIES==========================================================================
DIR_SRC		:= src/
DIR_INC 	:= includes/
DIR_BUILD	:= .build/


# FLAGS & COMPILATOR SETTINGS =========================================================
CC 			:= cc
DEPS_FLAGS	:= -MMD -MP
WARN_FLAGS	:= -Wall -Wextra -Werror -g3 -O3 #-fsanitize=thread
C_FLAGS		:= $(WARN_FLAGS) $(DEPS_FLAGS)
INC_FLAGS	:= -I $(DIR_INC)

COMP 		:= $(CC) $(C_FLAGS) $(INC_FLAGS)

ANTI_RELINK	:= $(DIR_INC) $(DIR_INC_LIB)

# FUNCTIONS ===========================================================================
define generate_var_sources_dir
DIR_$(1) = $(addprefix $(DIR_SRC), $(shell echo $(1) | tr '[:upper:]' '[:lower:]')/)
endef

define generate_var_sources
SRC_$(1) = $(addprefix $(DIR_$(1)),$(F_$(1)))
endef

define generate_var_objects
OBJS_$(1) = $(patsubst $(DIR_SRC)%.c,$(DIR_BUILD)%.o,$(SRC_$(1)))
endef

define generate_var_deps
DEPS_$(1) = $(patsubst $(DIR_SRC)%.c,$(DIR_BUILD)%.d,$(SRC_$(1)))
endef



# COMPONENTS ==========================================================================

COMPONENTS	:=	PARSING					\
				DEBUG					\
				UTILS					\
				INIT					\
				EXEC					\
				SHARED_STATE			\

# FILES ===============================================================================

F_EXEC		:=	start_routine.c			\
				start_simulation.c		\
				time.c					\

F_INIT		:=	init_simulation.c		\

F_PARSING	:=	parse_argument.c		\
				init_sim_data.c			\
				ft_atoi.c				\
				is_all_digit.c			\

F_DEBUG		:=	print_sim.c				\

F_UTILS		:=	cleanup_resources.c		\

F_SHARED_STATE := shared_state.c		\

F_MAIN		:=	main.c					\

# VARS GENERATION =====================================================================
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_sources_dir,$(comp))))
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_sources,$(comp))))
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_objects,$(comp))))
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_deps,$(comp))))

OBJS := $(foreach comp, $(COMPONENTS), $(OBJS_$(comp))) \
		$(DIR_BUILD)main.o

DEPS := $(foreach comp, $(COMPONENTS), $(DEPS_$(comp))) \
		$(DIR_BUILD)main.d

# COMPILATION =========================================================================
$(NAME) : $(OBJS)
	$(COMP) $^ -o $@

$(DIR_BUILD) :
	mkdir -p $(DIR_BUILD)

$(DIR_BUILD)%.o : $(DIR_SRC)%.c $(ANTI_RELINK) | $(DIR_BUILD)
	mkdir -p $(dir $@)
	$(COMP) -c $< -o $@

-include $(DEPS)

# RULES ===============================================================================
# build -------------------------------------------------------------------------------
all : $(NAME) 

# clean -------------------------------------------------------------------------------
clean:
	@rm -rf $(DIR_BUILD)

fclean:
	rm -rf $(DIR_BUILD)
	rm -f $(NAME)

re: fclean
	$(MAKE) -j all

.DEFAULT_GOAL = all

# debug -------------------------------------------------------------------------------
print-%:
	@echo $($(patsubst print-%,%,$@))


.PHONY: all lib clean fclean re print-%
