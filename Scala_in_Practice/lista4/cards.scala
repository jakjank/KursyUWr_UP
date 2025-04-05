import Math.min

package cards{
    // val colors = List("club","diamond","spade","heart")
    // val values = (2 to 14).toList
    // class Card(val color: String, val value: Int){
    //     require((colors.contains(color) &&
    //             values.contains(value)), "Bad card")  
    //     override def toString : String =
    //         val display = value match {
    //             case 11 => "Jack"
    //             case 12 => "Queen"
    //             case 13 => "King"
    //             case 14 => "Ace"
    //             case n  => n.toString
    //         }
    //         s"($color, $display)"
        
    //     def ==(other : Card) : Boolean =
    //         color == other.color && value == other.value

    //     def BlackJackPoints() : Int =
    //         if(value == 14){
    //             return 11
    //         }
    //         Math.min(value,10)
    // }

    sealed abstract class Color
    case object Clubs extends Color
    case object Diamonds extends Color
    case object Hearts extends Color
    case object Spades extends Color

    sealed abstract class Rank
    case object Ace extends Rank
    case class Numerical(val n: Int) extends Rank {
        require(n >= 2 && n <= 10)
    }
    sealed abstract class Face extends Rank
    case object Jack extends Face
    case object Queen extends Face
    case object King extends Face

    case class Card(color: Color, rank: Rank){
        def BlackJackPoints() = 
            rank match {
                case y : Numerical => y.n
                case z : Face => 10
                case _ => 11 //not num, not face, so ace
            }
    }
    object Card {
        def apply(color: Color, rank: Int): Card =
            Card(color, Numerical(rank))
    }
}