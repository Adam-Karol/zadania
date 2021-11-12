import gi
 
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
 
 
class OknoZPolamiTekstowymi:
    def __init__(self):
        self.okno = Gtk.Window()
        self.okno.set_title("Entry i TextView")
        self.okno.resize(700, 350)
 
        self.przycisk = Gtk.Button(label='Wypisz zlozonosc programu!')
 
        self.box = Gtk.VBox();
        self.subbox = Gtk.HBox();
        self.box.pack_start(self.subbox, True, True, 20)
        self.okno.add(self.box)
 
        self.okno.connect("delete-event", Gtk.main_quit)
        self.przycisk.connect("button-press-event", self.on_button_press2)
        self.okno.connect("key-press-event", self.on_button_press3)
 
        self.rightbox = Gtk.VBox()
        self.subbox.pack_start(self.rightbox, True, True, 20)
        self.rightbox.pack_start(self.przycisk, True, True, 20)
 
        self.leftbox = Gtk.VBox()
        self.subbox.pack_start(self.leftbox, True, True, 20)
 
        # ENTRY #
        self.entry = Gtk.Entry()  # Utworznie obiektu pola do wpisywania.
        self.entry.set_text("Wpisz kod lub podaj lokalizacje pliku")
        self.leftbox.pack_start(self.entry, False, False, 20)  # Dodanie go do okna w odpowiednim miejscu.
        self.entry.grab_focus()  # Ustawia zaznaczenie pola (albo przycisku) - po włączeniu programu będziemy mogli od razu tutaj pisać.
 
        # TEXTVIEW #
        self.textview = Gtk.TextView()  # Utworzenie obiektu do wyświetlania tekstu.
        self.textview.set_editable(True)  # Wyłączenie możliwości edycji tego pola.
        self.buffer = Gtk.TextBuffer()  # Utworznie obiektu bufora przechowującego tekst, który ma się wyświetlać.
        self.textview.set_buffer(self.buffer)  # Podłączenie bufora do naszego pola do wyświetlania tesktu.
        self.leftbox.pack_start(self.textview, False, False, 20)  # Dodanie textview do okna.
 
        self.okno.show_all()
 
    def on_button_press2(self, *args):
        out = ""
        tekst = self.entry.get_text()
        if tekst[0] == "/":
            f = open(tekst, "r")
            tekst = f.read()
        licznik = 0
        maks = 0
        for linia in tekst.splitlines():
            if linia == "for":
                licznik += 1
                if licznik > maks:
                    maks += 1
            elif linia == "end":
                licznik -= 1
        if maks == 0:
            out = "O(1)"
        elif maks == 1:
            out = "O(n)"
        else:
            out = f"O(n^{maks})"
 
        self.buffer.set_text(out)  # Ustawiamy pobrany tekst w buforze. Jeśli bufor ten jest podłączony (set_buffer) do textview, to tekst ten wyświetli się w nim.
 
    def on_button_press3(self, obiekt_okna, zdarzenie):
        if zdarzenie.hardware_keycode == 36:
            self.on_button_press2()
 
 
okno = OknoZPolamiTekstowymi()
Gtk.main()