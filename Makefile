NAME = cub3D

C_FILES =	color_params.c \
			cub3d.c \
			cub_free.c \
			cub_init.c \
			draw_env.c \
			draw_ray_calc.c \
			draw_sprites.c \
			drawing.c \
			keymap.c \
			moving.c \
			moving_strafe.c \
			parse_map_router.c \
			parser_additional.c \
			parser_body.c \
			parser_router.c \
			player_params.c \
			sprite_params.c \
			take_screenshot.c \
			work_with_map.c \
			get_next_line.c \
			get_next_line_utils.c

O_FILES = $(C_FILES:.c=.o)
HEADER = cub3d.h

.PHONY: all bonus clean fclean re
all: $(NAME)
$(NAME): $(O_FILES)
	@make bonus -C ./libft
	@make -C ./mlx
	@make -C ./dymlx
	mv ./dymlx/libmlx.dylib ./
	gcc -g $(O_FILES) ./libft/libft.a ./mlx/libmlx.a libmlx.dylib -framework OpenGL -framework Appkit -o $(NAME)
%.o: %.c $(HEADER)
	@gcc -c $<
clean:
	@rm -f $(O_FILES)
	@make clean -C ./libft
	@make clean -C ./mlx
	@make clean -C ./dymlx
fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib
	@make fclean -C ./libft
bonus: re
re: fclean all
