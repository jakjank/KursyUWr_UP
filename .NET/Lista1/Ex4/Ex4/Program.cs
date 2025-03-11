namespace Ex4
{
    public class Plant
    {
        /// <summary>
        /// statyczne maxID do nadawania unikalnych ID roslinom
        /// </summary>
        private static int maxID = 1;
        /// <summary>
        /// ID jednoznacznie definiujace rosline
        /// </summary>
        public int ID;
        /// <summary>
        /// gatunek rosliny
        /// </summary>
        public String species;
        /// <summary>
        /// wiek rosliny (w dniach)
        /// </summary>
        public int age;
        /// <summary>
        /// ilosc dni od ostatniego podlania
        /// </summary>
        public int unwateredDays;

        /// <summary>
        /// Konstruktor dal kalsy Plant
        /// </summary>
        /// <param name="species"></param>
        public Plant(string species)
        {
            ID = maxID;
            maxID++;
            this.species = species;
            this.age = 0;
            this.unwateredDays = 0;
        }


        public delegate void noWaterHandler(string species);

        public event noWaterHandler noWater;

        /// <summary>
        /// Metoda dajaca znać, ze roslina zostala podlana.
        /// unwateredDays = 0
        /// </summary>
        public void water()
        {
            this.unwateredDays = 0;
        }

        /// <summary>
        /// Metoa wypisujaca dane rosliny
        /// </summary>
        public void print()
        {
            Console.WriteLine($"Species: {species}");
            Console.WriteLine($"Age: {age} days");
            Console.WriteLine($"last time watered {unwateredDays} days ago");
        }

        /// <summary>
        /// metoda imitujaca uplyw jednego dnia dla rosliny
        /// </summary>
        public void dayPasses()
        {
            age++;
            unwateredDays++;
            if (unwateredDays > 5)
            {
                noWater?.Invoke(this.species);
            }
        }
    }

    public class Garden
    {
        /// <summary>
        /// Lista roslin w ogodzie
        /// </summary>
        private List<Plant> plants = [];

        /// <summary>
        /// Metoda pozwalajaca dodac rosline do ogrodu
        /// </summary>
        /// <param name="plant"></param>
        public void addPlant(Plant plant)
        {
            plant.noWater += species => plantNeedsWater(species);
            this.plants.Add(plant);
        }

        /// <summary>
        /// metoda informujaca uzytkownika rosliny jakiego rodzaju nalezy podlac
        /// </summary>
        /// <param name="species"></param>
        public void plantNeedsWater(String species)
        {
            Console.WriteLine($"You need to water {species}");
        }

        /// <summary>
        /// Metoda aplikujaca deszcz (podlanie wszystich roslin w ogrodzie
        /// </summary>
        public void rained()
        {
            foreach (Plant plant in plants)
            {
                plant.water();
            }
        }

        /// <summary>
        /// metoda podlawajaca rosliny konkretnego gatunku
        /// </summary>
        /// <param name="species"></param>
        public void waterSpecies(String species)
        {
            foreach (Plant plant in plants)
            {
                if (plant.species == species)
                {
                    plant.water();
                }
            }
        }

        /// <summary>
        /// Imituje uplyw dnia w ogrodzie
        /// </summary>
        public void dayPasses()
        {
            foreach (Plant plant in plants)
            {
                plant.dayPasses();
            }
        }

        /// <summary>
        /// Wypisuje rosliny w naszym ogrodzie
        /// </summary>
        public void showPlants()
        {
            foreach (Plant plant in plants)
            {
                Console.WriteLine("-------------------------");
                plant.print();
            }
            Console.WriteLine("-------------------------");
        }
    }



    public class Program
    {
        public static void Main()
        {
            Garden garden = new Garden();

            while (true)
            {
                Console.WriteLine("1. Add plant");
                Console.WriteLine("2. Show plants");
                Console.WriteLine("3. Water plants");
                Console.WriteLine("4. Rained");
                Console.WriteLine("5. Exit");
                Console.Write("Choose option: ");
                string choice = Console.ReadLine();
                string species;

                switch (choice)
                {
                    case "1":
                        Console.Write("Species of the new plant: ");
                        species = Console.ReadLine();
                        garden.addPlant(new Plant(species));
                        break;
                    case "2":
                        garden.showPlants();
                        break;
                    case "3":
                        Console.Write("choose species to water: ");
                        species = Console.ReadLine();
                        garden.waterSpecies(species);
                        break;
                    case "4":
                        garden.rained();
                        break;
                    case "5":
                        return;

                    default:
                        Console.WriteLine("Nothing happened today");
                        break;
                }
                garden.dayPasses();
                //Console.Clear();
            }
        }
    }
}