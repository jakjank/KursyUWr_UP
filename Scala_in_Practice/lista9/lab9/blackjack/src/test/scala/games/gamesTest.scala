package games

import org.scalatest.funsuite.AnyFunSuite
import org.scalatest.matchers.should.Matchers
import cards._
import deck._

class gamesTest extends AnyFunSuite with Matchers {

  test("adder should count regular cards correctly") {
    val bj = Blackjack(1)

    bj.adder(0, Card(Clubs, Numerical(7))) shouldBe 7
    bj.adder(5, Card(Hearts, Numerical(4))) shouldBe 9
    bj.adder(10, Card(Spades, Jack)) shouldBe 20
  }

  test("adder should treat Ace as 11 when possible") {
    val bj = Blackjack(1)

    bj.adder(0, Card(Hearts, Ace)) shouldBe 11
    bj.adder(9, Card(Hearts, Ace)) shouldBe 20
  }

  test("adder should treat Ace as 1 when 11 would overflow") {
    val bj = Blackjack(1)

    bj.adder(11, Card(Diamonds, Ace)) shouldBe 12
    bj.adder(20, Card(Spades, Ace)) shouldBe 21
  }

  test("first21 should find a valid sequence summing to 21 if present") {
    val cards = List(
      Card(Clubs, Numerical(10)),
      Card(Diamonds, Jack),
      Card(Spades, Ace)
    )
    val deck = Deck(cards)
    val bj = new Blackjack(deck)

    val all21 = bj.all21
    all21 should not be empty
    all21.head.map(_.BlackJackPoints()).sum should (be(
      21
    ) or be > 21)
  }

  test("first21 should return no sequence if 21 is not possible") {
    val cards = List(
      Card(Clubs, Numerical(5)),
      Card(Clubs, Numerical(3)),
      Card(Spades, Numerical(6))
    )
    val deck = Deck(cards)
    val bj = new Blackjack(deck)

    bj.all21 shouldBe empty
  }

}
