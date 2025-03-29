import deck._
import cards._
import scala.util.Random.shuffle

package games{

    class Blackjack(deck: Deck) {
        // Points calculation:
        // 1. Numerical cards as their numerical value = 2 - 10.
        // 2. Face cards (Jack, Queen, King) = 10
        // 3. Ace = 1 or 11 (player could choose)
        def adder(points : Int, card : Card) : Int =
                val cardPoints = card.BlackJackPoints()
                if(cardPoints == 11){
                    if(points + cardPoints <= 21){
                        return points + cardPoints
                    }
                    else{
                        return points + 1
                    }
                }
                points + cardPoints
        // loop taking n cards from the deck, pretty-printing them with points &
        // printing the sum of points on the end
        def play(n: Int): Unit =
            val (taken, remaining) = deck.cards.splitAt(n)
            var totalPoints = 0
            taken.foreach{ card =>
                totalPoints = adder(totalPoints, card)
                val cardPoints = card.BlackJackPoints()
                if(cardPoints == 11){ //Ace
                    println(s"$card , 1 or 11")
                }
                else{
                    println(s"$card , $cardPoints")
                }
            }
            println(totalPoints)
            // deck = Deck(remaining) sensible but deck is val so?

        // finds all subsequences of cards which could give 21 points
        lazy val all21: List[List[Card]] =
            def find21(remaining : List[Card], curWindow : List[Card],
                       result : List[List[Card]]) : List[List[Card]] =
                if(remaining.isEmpty){ return result }
                // val curPoints = curWindow.map(x => adder(0,x)).sum (bad for ex. 10,10,ace)
                var curPoints = 0
                for(c <- curWindow){
                    curPoints = adder(curPoints, c)
                }
                if(curPoints == 21){
                    return find21(remaining, curWindow.tail , result :+ curWindow)
                } else if(curPoints < 21){
                    return find21(remaining.tail, curWindow ::: List(remaining.head), result)
                } // curPoints > 21)
                find21(remaining, curWindow.tail, result)
            find21(deck.cards, Nil, Nil)

        // finds and pretty-prints the first subsequence of cards which could give 21 points
        def first21(): Unit = 
            if(all21.isEmpty) { println("No winning subsequences")}
            else{
                (for{
                    card <- all21.head
                } println(card))
            }
    }
    object Blackjack {
        // creates Blackjack game
        // having numOfDecks-amount of standard decs with random order
        // of cards. For example, with Blackjack(3) deck would have 156 cards
        def apply(numOfDecks: Int) = 
            new Blackjack(Deck.apply())
            val combinedCards = List.fill(numOfDecks)(Deck().cards).flatten
            new Blackjack(Deck(shuffle(combinedCards)))
    }


}