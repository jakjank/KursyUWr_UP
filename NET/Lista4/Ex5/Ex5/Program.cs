public class Program
{
    public static void Main()
    {
        var nameSurPes = File.ReadLines("ImieNazwiskoPesel.txt")
            .Select(line =>
            {
                var parts = line.Split(' ');
                return new
                {
                    Imie = parts[0],
                    Nazwisko = parts[1],
                    Pesel = parts[2]
                };
            });
        var pesAcc = File.ReadLines("PeselKonto.txt")
            .Select(line =>
            {
                var parts = line.Split(' ');
                return new
                {
                    Pesel = parts[0],
                    NumerKonta = parts[1]
                };
            });
    
        var joined = nameSurPes.Join(
            pesAcc,
            osoba => osoba.Pesel,
            konto => konto.Pesel,
            (osoba, konto) => new
            {
                osoba.Imie,
                osoba.Nazwisko,
                osoba.Pesel,
                konto.NumerKonta
            });

        foreach (var rekord in joined)
        {
            Console.WriteLine($"{rekord.Imie} {rekord.Nazwisko} {rekord.Pesel} {rekord.NumerKonta}");
        }
    }
}