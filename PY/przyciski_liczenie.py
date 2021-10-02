import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class OknoZPolamiTekstowymi:
    def __init__(self):
    
    
    
        self.okno = Gtk.Window()
        self.okno.set_title("ZLICZANIE")
        self.okno.resize(500, 350)
        
        self.box = Gtk.VBox();

        self.przycisk1 = Gtk.Button(label='LEWY P.')
        self.przycisk2 = Gtk.Button(label='PRAWY P.')

        self.subbox1 = Gtk.HBox();
        self.subbox2 = Gtk.HBox();
        self.box.pack_start(self.subbox1, True, True, 20)
        self.box.pack_start(self.subbox2, True, True, 20)
        self.okno.add(self.box)
        
        self.subbox2.pack_start(self.przycisk1, True, True, 20)
        self.subbox2.pack_start(self.przycisk2, True, True, 20)

        self.okno.connect("delete-event", Gtk.main_quit)
        self.przycisk1.connect("button-press-event", self.on_button_press1)
        self.przycisk2.connect("button-press-event", self.on_button_press2)

        self.licz1 = 0
        self.licz2 = 0

        # SUBBOX 1 #
        self.textview = Gtk.TextView() # Utworzenie obiektu do wyświetlania tekstu.
        self.textview.set_editable(False) # Wyłączenie możliwości edycji tego pola.
        self.buffer = Gtk.TextBuffer() # Utworznie obiektu bufora przechowującego tekst, który ma się wyświetlać.
        self.textview.set_buffer(self.buffer) # Podłączenie bufora do naszego pola do wyświetlania tesktu.
        self.subbox1.pack_start(self.textview, True, True, 20) # Dodanie textview do okna.
        
        
        self.textview2 = Gtk.TextView() # Utworzenie obiektu do wyświetlania tekstu.
        self.textview2.set_editable(False) # Wyłączenie możliwości edycji tego pola.
        self.buffer2 = Gtk.TextBuffer() # Utworznie obiektu bufora przechowującego tekst, który ma się wyświetlać.
        self.textview2.set_buffer(self.buffer2) # Podłączenie bufora do naszego pola do wyświetlania tesktu.
        self.subbox1.pack_start(self.textview2, True, True, 20) # Dodanie textview do okna.
        


        self.okno.show_all()

    # Wyświetla wpisany tekst w konsoli.
    def on_button_press1(self, obiekt_okna, zdarzenie):
        self.licz1 += 1 # Pobieramy tekst z pola wejściowego.
        self.buffer.set_text(str(self.licz1)) # Ustawiamy pobrany tekst w buforze. Jeśli bufor ten jest podłączony (set_buffer) do textview, to tekst ten wyświetli się w nim.

    # Wyświetla wpisany tekst w polu textview.
    def on_button_press2(self, obiekt_okna, zdarzenie):
        self.licz2 += 1 # Pobieramy tekst z pola wejściowego.
        self.buffer2.set_text(str(self.licz2)) # Ustawiamy pobrany tekst w buforze. Jeśli bufor ten jest podłączony (set_buffer) do textview, to tekst ten wyświetli się w nim.
        

okno = OknoZPolamiTekstowymi()
Gtk.main()
