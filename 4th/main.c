#include <gtk/gtk.h>

/*
  @Description: 从一个图片中获取信息得到pixbuf
  @param:       gchar filename
*/
GdkPixbuf *create_pixbuf(const gchar * filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    /*
     * 函数gdk_pixbuf_new_from_file() 从一个图片文件中加载图象数据，从而生成一个新的 pixbuf，
     * 至于文件中包含图象的格式，是由系统自动检测的。如果该函数返回值是NULL 的话，程序就会出现错误。
    */
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}


int main( int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;            //盒装容器
    GtkWidget *menubar;         //菜单栏
    GtkWidget *menutoggle, *menu_tog_toggle,*menu_tog_toolbar, *menu_tog_statusbar;  //界面开关菜单
    //GtkWidget *menu_about, *menu_about_us;  //帮助菜单

    /*初始化整个GTK+程序，是每一个GTK+程序必不可少的部分*/
    gtk_init(&argc, &argv);
    /*这里生成了一个窗口构件——GtkWindow，GTK_WINDOW_TOPLEVEL包含窗口的标题栏和边框，同意用窗口管理器来进行管理*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window), "一步一步学GTK+ DEMO");
    /*设置窗口默认大小*/
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    /*
     * 设置窗口在显示器中的位置为居中。
     *   GTK_WIN_POS_NONE            ：不固定
     *   GTK_WIN_POS_CENTER          : 居中
     *   GTK_WIN_POS_MOUSE           : 出现在鼠标位置
     *   GTK_WIN_POS_CENTER_ALWAYS   : 窗口改变大小的时候仍然居中
    */
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);


    /*创建一个盒装容器并添加到窗口中*/
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /*创建菜单*/
    menubar = gtk_menu_bar_new();   //代表整个菜单,是一个menu shell

    menutoggle = gtk_menu_new();   //这里代表第一列菜单toggle ,也是一个menu shell
    menu_tog_toggle = gtk_menu_item_new_with_label("widget toggle");
    menu_tog_toolbar = gtk_menu_item_new_with_label("show Toolbar"); //toggle 菜单中子项
    menu_tog_statusbar = gtk_menu_item_new_with_label("show Statusbar");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_tog_toggle), menutoggle);  //widget toggle菜单加入 menutoggle menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menutoggle), menu_tog_toolbar);
    gtk_menu_shell_append(GTK_MENU_SHELL(menutoggle), menu_tog_statusbar);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_tog_toggle);


    /*把菜单加入盒子容器*/
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
    /***********************************以下是信号处理部分************************************/

    /*关闭窗口时退出主循环*/
    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);

    /***********************************以下是显示控件部分************************************/
    /*开始显示窗口*/
    //gtk_widget_show(window);
    gtk_widget_show_all(window);


    gtk_main();
    return 0;
}
