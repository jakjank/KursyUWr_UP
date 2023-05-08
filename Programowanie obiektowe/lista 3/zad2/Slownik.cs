namespace zad2
{
    class MyDictionary<K , V>
    {
        public K? my_key;
        public V? my_val;
        public MyDictionary<K , V>? next;



        public void dodaj(K key , V val)
        {
            if(key is not null)
                if(key.Equals(this.my_key))
                {   
                    //jeśli znajdujemy pasujący klucz,
                    //to podmieniamy wartosci
                    this.my_val = val;
                    return;
                }
            

            if(this.next == null)
            {
                //jeśli dotarlismy do końca słownika,
                //to dodajemy w nim  nową pozycję 
                //z danym kluczem i wartością
                this.my_key = key;
                this.my_val = val;
                this.next = new MyDictionary<K , V>();
                //zawsze mamy jedną dodatkową "pustą"
                //pozycję na końcu słownika
            }
            else
            {
                //skoro to nie ten klucz ani nie koniec
                //słownika, to szukamy dalej
                this.next.dodaj(key , val);
            }
        }

        public V? wyszukaj(K key)
        {
            if(this.next == null)
            {
                return default(V); 
                //zwracamy wart. domyślną V bo nie ma
                //danego klucza w słowniku
            }
            else
            {
                if(key is not null)
                    if(key.Equals(this.my_key))
                    {
                        return my_val;
                        //zwracamy wartość która jest przy
                        //danym kluczu
                    }
                
            }

            return this.next.wyszukaj(key);
            //skoro nie znależliśmy pasującego klucza,
            //to przechodzimy do kolejnej komorki i
            //powtarzamy szukanie pasującego klucza
        }

        public void usun(K key)
        {
            //sprawdzamy czy dotarliśmy na koniec słownika
            if(this.next != null)
            {
                if(key is not null)
                    //sprawdzamy czy klucz pasuje
                    if(key.Equals(this.my_key))
                    {
                        this.my_val = this.next.my_val;
                        this.my_key = this.next.my_key;
                        this.next = this.next.next;
                        return;
                        //robimy podmiane tej pozycji na kolejną w 
                        //słowinku, a kolejną "przeskakujemy"
                        //żeby się nie powtarzała
                    }
                
                this.next.usun(key);
                //skoro to nie koniec słownika i nie ten klucz
                //to szukamy dalej
            }

        }
    }
}
