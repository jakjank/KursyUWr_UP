// Ex4, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// Program
using System;

internal class Program
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
			switch (Console.ReadLine())
			{
			case "1":
			{
				Console.Write("Species of the new plant: ");
				string species = Console.ReadLine();
				garden.addPlant(new Plant(species));
				break;
			}
			case "2":
				garden.showPlants();
				break;
			case "3":
			{
				Console.Write("choose species to water: ");
				string species = Console.ReadLine();
				garden.waterSpecies(species);
				break;
			}
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
		}
	}
}
