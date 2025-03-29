import cards.{Card, colors, values}
import scala.util.Random.shuffle

package deck{
    case class Deck(cards: List[Card]) {
        //creates new deck without first card
        def pull() = new Deck(cards.tail)
        //creates new deck with given card pushed on top
        def push(c: Card) : Deck = new Deck(c :: cards)
        //creates new deck with new card(color, value) pushed on top
        def push(color: String, value: Int) : Deck = push(new Card(color,value))
        
        // checks if deck is a standard deck
        val isStandard: Boolean = 
            (for{
                card <- cards
                if duplicatesOfCard(card) == 1
            } yield 1).sum == 52
        //amount of duplicates of the given card in the deck
        def duplicatesOfCard(card: Card): Int = 
            //cards.count(_ == card)
            (for{
                deck_card <- cards
                if deck_card == card
            } yield 1).sum
        //amount of cards in the deck for the given color
        def amountOfColor(color: String): Int =
            cards.count(_.color == color)
        //amount of cards in the deck for given numerical card (2, 3, 4, 5, 6, 7, 8, 9, 10)
        def amountOfNumerical(numerical: Int): Int =
            require(1 < numerical && 11 > numerical, "for Jack-Ace use amountOfFace")
            cards.count(_.value == numerical)
        //amount of all numerical cards in the deck (2, 3, 4, 5, 6, 7, 8, 9, 10)
        val amountWithNumerical: Int = 
            (for{
                card <- cards
                if card.value < 11
            } yield 1).sum
        //amount of cards in the deck for the given face (Jack, Queen & King)
        def amountOfFace(face: String) : Int =  
            require(face == "Jack" || face == "Queen" || face == "King" || face == "Ace",
                    "return amount of Jacks - Aces in the deck")
            if( face == "Jack" ){
                return cards.count(_.value == 11)
            }
            if( face == "Queen" ){
                return cards.count(_.value == 12)
            }
            if( face == "King" ){
                return cards.count(_.value == 13)
            }
            return cards.count(_.value == 14)
        //amount of all cards in the deck with faces (Jack, Queen & King)
        val amountWithFace: Int = 
            (for{
                card <- cards
                if card.value >= 11
            } yield 1).sum
        // override def toString : String =
        //     (for{
        //         card <- cards
        //     } yield card.toString).toString
    }

    object Deck{
        //creates the standard deck with random
        //order of cards. Check Random.shuffle1 function
        def apply() =
            // case class but without 'new' break
            new Deck(
                shuffle(
                    (for {
                    color <- colors
                    value <- values
                } yield new Card(color,value)))
            )
    }
}