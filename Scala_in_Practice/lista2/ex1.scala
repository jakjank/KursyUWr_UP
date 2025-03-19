package numbers{
    import Math.sqrt

    class Rational(val nom: Int, val denom: Int){
        require(denom > 0, "denominator cannot be '0'")
        def +(other: Rational): Rational = 
            Rational((nom * other.denom) + (other.nom * denom), denom * other.denom)
        def -(other: Rational): Rational =
            Rational((nom * other.denom) - (other.nom * denom), denom * other.denom)
        def *(other: Rational): Rational = 
            Rational(nom * other.nom, denom * other.denom)
        def /(other: Rational): Rational = 
            Rational(nom* other.denom, denom * other.nom)
        def ==(other: Rational): Boolean = 
            nom * other.denom == other.nom * other.denom

        def gcd ( a : Int , b : Int ) : Int = if ( b ==0) a else gcd (b , a % b )
        override def toString = 
            val g = gcd(nom,denom)
            s"${nom/g}/${denom/g}" 
        
        def sqrt() : Rational = 
            Rational(Math.sqrt(nom).toInt, Math.sqrt(denom).toInt)
        def toDouble() : Double = 
            nom.toDouble / denom.toDouble
    }

    object Rational{
        val zero: Rational = new Rational(0,1)
        val one: Rational = new Rational(1,1)
        def apply(nom: Int, denom: Int = 1): Rational = new Rational(nom, denom)
    }
}

package figures {
    import numbers.Rational

    class Point(val x : Rational, val y : Rational){
        override def toString = 
            s"(${x}, ${y})"
        def squaredDistance(p2: Point): Rational = 
            (x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y)
    }

    abstract class Shape() {
        def area : Rational
        val description : String
        override def toString = description + ", size: " + area
    }

    class Triangle(a : Point, b : Point, c : Point) extends Shape{
        require(area != Rational.zero, "Points cannot be colinear")
        def area = Rational(1,2) * (a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y - b.y))
        val description = "Triangle"
    }

    class Rectangle(a : Point, b : Point, c : Point, d : Point) extends Shape{
        require(isValidRectangle, "Given points do not create valid rectangle")
        def isValidRectangle: Boolean = {
            val sides = List(a.squaredDistance(b), b.squaredDistance(c), c.squaredDistance(d), d.squaredDistance(a))
            sides(0) == sides(2) && sides(1) == sides(3) // Opposite sides must be equal
        }
        def area = a.squaredDistance(b).sqrt() * a.squaredDistance(d).sqrt()
        val description = "Reactangle"
    }

    class Square(a : Point, b : Point) extends Shape{
        require(a.x != b.x || a.y != b.y, "Square cannot be inf. small")
        def area = a.squaredDistance(b)
        val description = "Square"
    }

    object ShapeFunct {
        def areaSum(figures: List[Shape]): Double = 
            var sum = Rational.zero
            for{ figure <- figures } sum = sum + figure.area
            sum.toDouble()
        def printAll(figures: List[Shape]): Unit = 
            for{
                figure <- figures
            } println(figure)
    }
}

object MyApplication {
    def main ( args: Array [String]) = // error on slides??
        import numbers.Rational
        val myRat = Rational(3,4)
        val newRat = myRat * Rational(2,3)
        // val Rat = Rational(2,0)
        println(Rational.zero)
        println(Rational.one)
        println(Rational(7))
        println(newRat)

        import figures.*
        val myTriangle =   figures.Triangle(Point(Rational(0,1),Rational(0,1)),
                                            Point(Rational(1,1),Rational(0,1)),
                                            Point(Rational(0,1),Rational(1,1)))

        val mySquare =       figures.Square(Point(Rational.zero, Rational.zero),
                                            Point(Rational(3,1), Rational.zero))

        val myRectangle = figures.Rectangle(Point(Rational.zero, Rational.zero),
                                            Point(Rational.zero, Rational(2,1)),
                                            Point(Rational(3,1), Rational(2,1)),
                                            Point(Rational(3,1), Rational.zero)) 
        
        ShapeFunct.printAll(List(myTriangle, mySquare, myRectangle))
        println(ShapeFunct.areaSum(List(myTriangle, mySquare, myRectangle)))
    
}