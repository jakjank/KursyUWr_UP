import cards.*
import scala.util.Random.shuffle
import scala.io.Source

package deck{
    case class Deck(cards: List[Card]) {
        //creates new deck without first card
        def pull() : Deck = 
            cards match {
                case Nil => throw new IllegalStateException("Cannot draw card from empty deck!")
                case x::xs => new Deck(xs)
            }
        //creates new deck with given card pushed on top

        def push(c: Card) : Deck = new Deck(c :: cards)
        //creates new deck with new card(color, value) pushed on top

        def push(color: Color, value: Rank) : Deck = push(new Card(color,value))
        
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
        def amountOfColor(color: Color): Int =
            cards.count(_.color == color)

        //amount of cards in the deck for given numerical card (2, 3, 4, 5, 6, 7, 8, 9, 10)
        def amountOfNumerical(numerical: Numerical): Int =
            cards.count(_.rank == Numerical)

        //amount of all numerical cards in the deck (2, 3, 4, 5, 6, 7, 8, 9, 10)
        val amountWithNumerical: Int = 
            cards.count{
                card => {
                    card.rank match {
                        case x : Numerical => true
                        case _ => false
                    }
                }
            }
        
        //amount of cards in the deck for the given face (Jack, Queen & King)
        def amountOfFace(face: Face) : Int =
            cards.count(_.rank == face)
            
        //amount of all cards in the deck with faces (Jack, Queen & King)
        val amountWithFace: Int = 
            cards.count{
                card => {
                    card.rank match {
                        case x : Face => true
                        case _ => false
                    }
                }
            }
    }

    object Deck{
        //creates the standard deck with random
        //order of cards. Check Random.shuffle1 function
        def apply() =
            // case class but without 'new' break
            new Deck(
                shuffle(
                    (for {
                        color <- List(Clubs, Diamonds, Hearts, Spades)
                        rank <- (2 to 10).map(Numerical(_)) ++ List(Ace, Jack, Queen, King)
                    } yield new Card(color,rank)))
            )
    }
}