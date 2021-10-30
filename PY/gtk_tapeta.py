import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf

class Okno:
    def __init__(self):
        self.okno = Gtk.Window()
        self.okno.move(78, 151)
        self.okno.resize(600, 600)

        self.okno.connect("delete-event", self.wyjscie)

        pixbuf = GdkPixbuf.Pixbuf.new_from_file("/home/adam/Desktop/tapeta.png")
        pixbuf = pixbuf.scale_simple(1920, 1080, GdkPixbuf.InterpType.HYPER)
        pixbuf = pixbuf.new_subpixbuf(200, 200, 800, 800)

        image = Gtk.Image()
        image.set_from_pixbuf(pixbuf)

        self.okno.add(image)
        self.okno.show_all()

    def wyjscie(self, *args):
        print("Zamknieto program")
        print(self.okno.get_position())
        Gtk.main_quit()

okno = Okno()
Gtk.main()
