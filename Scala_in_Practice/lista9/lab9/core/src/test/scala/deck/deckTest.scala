package deck

import org.scalatest.funsuite.AnyFunSuite
import org.scalatest.matchers.should.Matchers
import cards._

class deckTest extends AnyFunSuite with Matchers {

  test("Deck.apply should create a standard 52-card deck") {
    val deck = Deck()
    deck.cards should have size 52
    deck.isStandard shouldBe true
  }

  test("Deck.pull removes the top card from the deck") {
    val deck = Deck()
    val newDeck = deck.pull()
    newDeck.cards should have size 51
    deck.isStandard shouldBe false
  }

  test("Deck.pull throws when deck is empty") {
    val emptyDeck = Deck(Nil)
    an[IllegalStateException] should be thrownBy emptyDeck.pull()
  }

  test("Deck.push should add a card on top") {
    val card = Card(Clubs, Numerical(5))
    val deck = Deck(Nil)
    val newDeck = deck.push(card)
    newDeck.cards.head shouldBe card
  }

  test("Deck.duplicatesOfCard should return 1 in standard deck") {
    val card = Card(Clubs, Ace)
    val deck = Deck()
    deck.duplicatesOfCard(card) shouldBe 1
  }

  test("Deck.amountOfColor should count all cards of given color") {
    val deck = Deck()
    deck.amountOfColor(Hearts) shouldBe 13
  }

  test(
    "Deck.amountOfNumerical should count cards with specific numerical rank"
  ) {
    val deck = Deck()
    println(deck)
    deck.amountOfNumerical(Numerical(7)) shouldBe 4
  }

  test("Deck.amountWithNumerical should count all numerical cards") {
    val deck = Deck()
    deck.amountWithNumerical shouldBe 36 // 9 ranks * 4 suits
  }

  test("Deck.amountOfFace should count cards with specific face") {
    val deck = Deck()
    deck.amountOfFace(Jack) shouldBe 4
    deck.amountOfFace(Queen) shouldBe 4
    deck.amountOfFace(King) shouldBe 4
  }

  test("Deck.amountWithFace should count all face cards") {
    val deck = Deck()
    deck.amountWithFace shouldBe 12
  }
}
