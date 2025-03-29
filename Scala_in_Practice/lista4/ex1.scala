import deck._
import games._
import games._

@main
def main =
    var mydeck = Deck.apply()

    println(mydeck)
    println(s"is standard? ${mydeck.isStandard}")

    for (i <- (0 to 47)){
        mydeck = mydeck.pull()
    }
    println("After pulling 48 cards")
    println(mydeck)
    println(s"is standard? ${mydeck.isStandard}")

    mydeck = mydeck.push("diamond", 13)
    println(mydeck)

    println(s"amount of 'diamond's = ${mydeck.amountOfColor("diamond")}")
    println(s"amount of 'King's = ${mydeck.amountOfFace("King")}")
    println(s"amount of 7s = ${mydeck.amountOfNumerical(7)}")
    println(s"amount with nums = ${mydeck.amountWithNumerical}")
    println(s"amount with faces = ${mydeck.amountWithFace}")

    println("------------------------------- blackjack part")

    val blackjack = Blackjack.apply(2)
    println("all 21:")
    for(list <- blackjack.all21){
        println(list)
    }

    println("\nfirst 21:")
    blackjack.first21()

    println("\nplay(4):")
    blackjack.play(4)
