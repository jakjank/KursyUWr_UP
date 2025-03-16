namespace EX1
{
    public partial class Dog(string name)
    {
        // readonly allows for assigning value only while initialization or in constructor
        private readonly string name;
        //public Dog(string name)
        //{
        //    this.name = name;
        //}

        public string GetName()
        {
            return this.name;
        }
    }
}