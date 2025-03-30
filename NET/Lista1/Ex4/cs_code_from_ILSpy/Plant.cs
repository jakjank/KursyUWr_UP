// Ex4, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// Plant
using System;

internal class Plant
{
	public delegate void noWaterHandler(string species);

	private static int maxID = 1;

	public int ID;

	public string species;

	public int age;

	public int unwateredDays;

	public event noWaterHandler noWater;

	public Plant(string species)
	{
		ID = maxID;
		maxID++;
		this.species = species;
		age = 0;
		unwateredDays = 0;
	}

	public void water()
	{
		unwateredDays = 0;
	}

	public void print()
	{
		Console.WriteLine("Species: " + species);
		Console.WriteLine($"Age: {age} days");
		Console.WriteLine($"last time watered {unwateredDays} days ago");
	}

	public void dayPasses()
	{
		age++;
		unwateredDays++;
		if (unwateredDays > 5)
		{
			this.noWater?.Invoke(species);
		}
	}
}
