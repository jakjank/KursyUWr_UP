// Ex4, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// Garden
using System;
using System.Collections.Generic;

internal class Garden
{
	private List<Plant> plants = new List<Plant>();

	public void addPlant(Plant plant)
	{
		plant.noWater += delegate(string species)
		{
			plantNeedsWater(species);
		};
		plants.Add(plant);
	}

	public void plantNeedsWater(string species)
	{
		Console.WriteLine("You need to water " + species);
	}

	public void rained()
	{
		foreach (Plant plant in plants)
		{
			plant.water();
		}
	}

	public void waterSpecies(string species)
	{
		foreach (Plant plant in plants)
		{
			if (plant.species == species)
			{
				plant.water();
			}
		}
	}

	public void dayPasses()
	{
		foreach (Plant plant in plants)
		{
			plant.dayPasses();
		}
	}

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
