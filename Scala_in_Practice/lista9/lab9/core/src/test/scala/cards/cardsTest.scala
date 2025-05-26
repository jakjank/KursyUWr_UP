package cards

import org.scalatest.funsuite.AnyFunSuite
import org.scalatest.matchers.should.Matchers

class cardsTest extends AnyFunSuite with Matchers {

  test("Blackjack points for Numerical cards") {
    Card(Clubs, Numerical(2)).BlackJackPoints() shouldBe 2
    Card(Diamonds, Numerical(10)).BlackJackPoints() shouldBe 10
  }

  test("Blackjack points for Face cards") {
    Card(Hearts, Jack).BlackJackPoints() shouldBe 10
    Card(Spades, Queen).BlackJackPoints() shouldBe 10
    Card(Clubs, King).BlackJackPoints() shouldBe 10
  }

  test("Blackjack points for Ace") {
    Card(Diamonds, Ace).BlackJackPoints() shouldBe 11
  }

  test("Card.apply creates a Numerical card") {
    val card = Card(Spades, 5)
    card.rank shouldBe Numerical(5)
    card.color shouldBe Spades
    card.BlackJackPoints() shouldBe 5
  }

  test("Two identical cards should be equal") {
    val c1 = Card(Hearts, Numerical(9))
    val c2 = Card(Hearts, Numerical(9))
    c1 shouldEqual c2
  }

  test("Different cards are not equal") {
    val c1 = Card(Hearts, Numerical(9))
    val c2 = Card(Hearts, Numerical(10))
    c1 should not equal c2
  }

  test("Numerical should throw if value < 2 or > 10") {
    assertThrows[IllegalArgumentException] {
      Numerical(1)
    }
    assertThrows[IllegalArgumentException] {
      Numerical(11)
    }
  }
}
