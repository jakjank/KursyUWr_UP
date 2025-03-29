import Math.min

package cards{
    val colors = List("club","diamond","spade","heart")
    val values = (2 to 14).toList
    class Card(val color: String, val value: Int){
        require((colors.contains(color) &&
                values.contains(value)), "Bad card")  
        override def toString : String =
            val display = value match {
                case 11 => "Jack"
                case 12 => "Queen"
                case 13 => "King"
                case 14 => "Ace"
                case n  => n.toString
            }
            s"($color, $display)"
        
        def ==(other : Card) : Boolean =
            color == other.color && value == other.value

        def BlackJackPoints() : Int =
            if(value == 14){
                return 11
            }
            Math.min(value,10)
    }
}