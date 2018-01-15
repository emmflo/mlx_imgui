OBJDIR := objs
OBJLIST := \
	imgui.o \
	imgui_utils.o
OBJS := $(addprefix $(OBJDIR)/,$(OBJLIST))
CC := clang
SRCDIR := srcs
INCDIR := includes
CFLAGS := -g -Wall -Wextra -I$(INCDIR) -I../minilibx/ -I../mlx_graphics/includes -I../libft/includes
NAME := libmlx_imgui.a

.PHONY : all clean fclean binclean re

all : $(NAME)
	
$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean :
	rm -rf $(OBJDIR)

binclean:
	rm -f $(NAME)

fclean : clean binclean

re : fclean all
