################################################################################
#                                     CONFIG                                   #
################################################################################
LFT			:= libft
FLAGS		:= -Wall -Werror -Wextra -g
LDFLAGS		:= -L./libft -lft
INCLUDE		:= -I./libft/include/
OBJDIR		:= obj

CC 			:= gcc $(FLAGS) $(INCLUDE)
################################################################################
#                                     COLOURS                                  #
################################################################################
CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
BLUE        := \033[1;34m
CYAN        := \033[1;36m
PURPLE      := \033[1;35m
BOLD        := \033[1m
################################################################################
#        :                     SOURCE & OBJECT FILES                            #
################################################################################
SOURCES := server.c client.c
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

ALL_OBJS := $(OBJECTS)
################################################################################
#                                 PROGRESS BAR                                 #
################################################################################
TOTAL_FILES = $(shell echo $(ALL_OBJS) | wc -w)
CURR_FILE   = 0

define progress_bar
$(eval CURR_FILE = $(shell expr $(CURR_FILE) + 1))
@printf "\r$(YELLOW)⌛ [%-50s] %d/%d files\n" "$$(printf '#%.0s' $$(seq 1 $$(expr $(CURR_FILE) \* 50 / $(TOTAL_FILES))))" $(CURR_FILE) $(TOTAL_FILES)
endef
################################################################################
#                                COMPILATION                                   #
################################################################################

all: check-and-reinit-submodules libft banner server client
	@printf "\n$(GREEN)✨ Project compiled successfully!$(CLR_RMV)\n"
	@printf "$(PURPLE)▶ Run $(BOLD)./server$(CLR_RMV) to start the server\n"
	@printf	"$(PURPLE)▶ $(BOLD)Run ./client PID STR $(CLR_RMV) to start the client\n"
	@printf 'use $(GREEN) gnome-terminal -- sh -c "./server" && ./client $$(pgrep -n server) $$(read -p "Input: " str && echo $$str)$(CLR_RMV) to run dynamically\n'

banner:
	@printf "%b" "$(CYAN)"
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║                         Building minitalk                     ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"
	@printf "%b" "$(CLR_RMV)"

server: $(OBJDIR)/server.o $(LFT)
	@printf "$(BLUE)🔨 Linking server...$(CLR_RMV)\n"
	@$(CC) -o $@ $< $(LDFLAGS)
	@printf "$(GREEN)✓ Server ready!$(CLR_RMV)\n"

client: $(OBJDIR)/client.o $(LFT)
	@printf "$(BLUE)🔨 Linking client...$(CLR_RMV)\n"
	@$(CC) -o $@ $< $(LDFLAGS)
	@printf "$(GREEN)✓ Client ready!$(CLR_RMV)\n"

$(OBJDIR)/%.o: %.c
	$(shell mkdir -p $(OBJDIR) 1> /dev/null)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call progress_bar)

libft:
	@printf "$(BLUE)📚 Building libft...$(CLR_RMV)\n"
	@make -C $(LFT)
	@printf "$(GREEN)✓ Libft ready!$(CLR_RMV)\n"

check-and-reinit-submodules:
	@if git submodule status | egrep -q '^[-+]'; then \
		echo "INFO: Need to reinitialize git submodules"; \
		git submodule update --init; \
    fi

clean:
	@printf "$(RED)🧹 Cleaning object files...$(CLR_RMV)\n"
	@rm -rf $(OBJECTS) $(OBJDIR)
	@printf "$(GREEN)✓ Clean complete!$(CLR_RMV)\n"

fclean: clean
	@printf "$(RED)🗑️  Removing executables...$(CLR_RMV)\n"
	@make -C $(LFT) fclean
	@rm -f server client
	@printf "$(GREEN)✓ Full clean complete!$(CLR_RMV)\n"

re: fclean all

.PHONY: all bonus libft check_clean clean fclean re
################################################################################
#                                     END                                      #
################################################################################

