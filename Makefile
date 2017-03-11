# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbauer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 16:26:20 by bbauer            #+#    #+#              #
#    Updated: 2017/03/10 17:15:36 by bbauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ft_ls
CC =				gcc
FLAGS =				-Wall -Werror -Wextra

FT_LS_SRC_DIR = 	./src/
FT_SRC_DIR =		./src/libft
PRINTF_SRC_DIR =	./src/ft_printf

FT_LS_OBJ_DIR =		./obj
FT_OBJ_DIR =		./obj/libft
PRINTF_OBJ_DIR =	./obj/ft_print

INCLUDES_DIR =		./includes

LIBFT_COMPILED = ft_atoi.o \
				 ft_bzero.o \
				 ft_isalnum.o \
				 ft_isalpha.o \
				 ft_isascii.o \
				 ft_isdigit.o \
				 ft_ishex.o \
				 ft_isprint.o \
				 ft_itoa.o \
				 ft_itoa_base.o \
				 ft_itoa_base_intmax.o \
				 ft_itoa_base_uintmax.o \
				 ft_itoa_base_ull.o \
				 ft_lst_append.o \
				 ft_lst_free_contents.o \
				 ft_lst_len.o \
				 ft_lstadd.o \
				 ft_lstdel.o \
				 ft_lstdelone.o \
				 ft_lstiter.o \
				 ft_lstmap.o \
				 ft_lstnew.o \
				 ft_nbrlen.o \
				 ft_memalloc.o \
				 ft_memccpy.o \
				 ft_memchr.o \
				 ft_memcmp.o \
				 ft_memcpy.o \
				 ft_memdel.o \
				 ft_memmove.o \
				 ft_memset.o \
				 ft_putchar.o \
				 ft_putchar_fd.o \
				 ft_putendl.o \
				 ft_putendl_fd.o \
				 ft_putnbr.o \
				 ft_putnbr_fd.o \
				 ft_putstr.o \
				 ft_putstr_fd.o \
				 ft_realloc.o \
				 ft_strcat.o \
				 ft_strchr.o \
				 ft_strclr.o \
				 ft_strcmp.o \
				 ft_strcpy.o \
				 ft_strdel.o \
				 ft_strdup.o \
				 ft_strequ.o \
				 ft_striter.o \
				 ft_striteri.o \
				 ft_strjoin.o \
				 ft_strlcat.o \
				 ft_strlen.o \
				 ft_strmap.o \
				 ft_strmapi.o \
				 ft_strncat.o \
				 ft_strncmp.o \
				 ft_strncpy.o \
				 ft_strndup.o \
				 ft_strnequ.o \
				 ft_strnew.o \
				 ft_strnstr.o \
				 ft_strrchr.o \
				 ft_strsplit.o \
				 ft_strstr.o \
				 ft_strsub.o \
				 ft_strtrim.o \
				 ft_tolower.o \
				 ft_tolower_str.o \
				 ft_toupper.o \
				 ft_toupper_str.o \
				 ft_utf8charencode.o \
				 ft_utf8charsize.o \
				 ft_utf8strencode.o \
				 ft_utf8strnencode.o \
				 ft_wchar_memset.o \
				 ft_wcharbits.o \
				 ft_wcharsize_utf8.o \
				 ft_wstrdup.o \
				 ft_wctomb.o \
				 ft_wrdcnt.o \
				 ft_wrdcntd.o \
				 ft_wrdlen.o \
				 ft_wrdsplit.o \
				 ft_wstrcpy.o \
				 ft_wstrlen.o \
				 ft_wstrndup.o \
				 ft_wstrnsize_utf8.o \
				 ft_wstrsize_utf8.o \
				 get_next_line.o


FT_PRINTF_COMPILED = apply_precision.o \
					 apply_prefix.o \
					 apply_width.o \
					 apply_width_wchar.o \
					 fix_sign_placement.o \
					 ft_printf.o \
					 ft_vprintf.o \
					 read_flags.o \
					 read_length.o \
					 read_precision.o \
					 read_specifier.o \
					 read_width.o \
					 verify_flag_compatibility.o \
					 verify_flag_compatibility_continued.o \
					 write_char.o \
					 write_conversion_substr.o \
					 write_hex.o \
					 write_octal.o \
					 write_signed_int.o \
					 write_string.o \
					 write_unsigned_int.o \
					 write_wchar.o \
					 write_wstring.o

FT_LS_COMPILED = ft_ls.o \
				 ft_ls_utilities.o \
				 open_dir.o \
				 print_with_stats.o \
				 process_and_print.o \
				 sorting.o

COMPILED = $(LIBFT_COMPILED) $(FT_PRINTF_COMPILED) $(FT_LS_COMPILED)

all: $(NAME)

$(NAME): $(COMPILED)
	@gcc $(FLAGS) -o $(NAME) $(COMPILED)
	@mkdir -p obj/ft_printf obj/ft_ls obj/libft
	@mv $(LIBFT_COMPILED) ./obj/libft
	@mv $(FT_LS_COMPILED) ./obj/$(NAME)
	@mv $(FT_PRINTF_COMPILED) ./obj/ft_printf
	@echo "made" $(NAME)

$(FT_LS_COMPILED): %.o: $(FT_LS_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(INCLUDES_DIR) $< -o $@

$(LIBFT_COMPILED): %.o: $(FT_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(INCLUDES_DIR) $< -o $@

$(FT_PRINTF_COMPILED): %.o: $(PRINTF_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(INCLUDES_DIR) $< -o $@

clean:
	@-/bin/rm -f $(COMPILED)
	@-/bin/rm -rf $(FT_LS_OBJ_DIR)
	@echo "cleaned" $(NAME)

fclean: clean
	@-/bin/rm -f $(NAME)
	@-/bin/rm -rf a.out a.out.dSYM
	@echo "fcleaned" $(NAME)

re: fclean all

