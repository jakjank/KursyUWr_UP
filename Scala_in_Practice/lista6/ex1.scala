import scala.util.matching.Regex

package pizzeria {
    abstract class PizzaType{
        val cost : Double
    }
    case object Margherita extends PizzaType{
        val cost = 5.0
    }
    case object Peperoni extends PizzaType{
        val cost = 6.5
    }
    case object Funghi extends PizzaType{
        val cost = 7.0
    }

    abstract class Size
    case object Small extends Size
    case object Medium extends Size
    case object Large extends Size

    abstract class Crust
    case object Thin extends Crust
    case object Thick extends Crust

    abstract class Extra {
        val cost : Double
    }

    abstract class Topping extends Extra{
        val cost : Double
    }
    case object Ketchup extends Topping {
        val cost = 0.5 
    }
    case object Garlic extends Topping{
        val cost  = 0.5 
    }

    abstract class Meat extends Extra
    case object Salami extends Meat{
        val cost = 1.0
    }

    abstract class Drink extends Extra
    case object Lemonade extends Drink{
        val cost = 2.0
    }

    abstract class Discount
    case object Student extends Discount
    case object Senior extends Discount
    

    case class Pizza(
            pizzaType: PizzaType,
            size: Size,
            crust: Crust,
            extraTopping: Option[Topping] = None, //optional topping
            extraMeat: Option[Meat] = None, //optional meat
            ) {
        //pretty print the pizza
        override def toString() = 
            val toppingStr = extraTopping.map(x => s", extra topping: $x").getOrElse("")
            val meatStr = extraMeat.map(x => s", extra meat: $x").getOrElse("")
            //val drinkStr = extraDrink.map(x => s", drink: $x").getOrElse("")
            //val discountStr = discount.map(x => s", discount: $x").getOrElse("")
            s"[type: $pizzaType, size: $size, crust: $crust$toppingStr$meatStr]"

        //calculated price for pizza. When type=small than price is 90% & if type=large than price is 150%
        val price: Double = 
            val toppingCost = extraTopping.map(_.cost).getOrElse(0.0)
            val meatCost = extraMeat.map(_.cost).getOrElse(0.0)
            
            val baseCost = pizzaType.cost + toppingCost + meatCost
            
            if (size == Large) 1.5 * baseCost
            else if (size == Small) 0.9 * baseCost
            else baseCost
    }

    package orders{
        import pizzeria._

        class Order(
            name: String,
            address: String,
            phone: String, //mandatory validated phone-number (hint: regex)
            pizzas: List[Pizza],
            extraDrink: Map[Drink, Int],
            discount: Option[Discount] = None, //optional value
            specialInfo: Option[String] = None//optional text, like: “Ring doesnt work, please knock” 
            ){
            private val phonePattern: Regex = "^(\\+\\d{2})?\\d{9}$".r
            require(phonePattern.matches(phone),s"invalid phone number: $phone")
        
            def extraMeatPrice: Double = //why Option[Double] = 
                pizzas.flatMap(_.extraMeat.map(_.cost)).sum
            def pizzasPrice: Double = //Option[Double] = 
                pizzas.map(_.price).sum
            def drinksPrice: Double = //Option[Double] =
                extraDrink.keys.map(k => k.cost * extraDrink(k)).sum
            //total price of all pizzas by type (Margarita, Pepperoni & Funghi)
            def priceByType(pizzaType: PizzaType): Double = //Option[Double] = ???
                pizzas.filter(_.pizzaType == pizzaType).map(_.price).sum

            val price: Double = 
                val basePrice = pizzasPrice + drinksPrice
                if (discount == Option(Senior)) 0.93*basePrice
                else if (discount == Option(Student)) 0.95*basePrice
                else basePrice

            override def toString(): String = {
                val pizzasStr = 
                    if (pizzas.nonEmpty)
                        pizzas.map(p => s"  - $p").mkString("\n")
                    else "  - None"
                val drinksStr = 
                    if (extraDrink.nonEmpty)
                        extraDrink.map((drink, count) => s"  - $drink x$count").mkString("\n")
                    else "  - None"

                val totalBeforeDiscount = pizzasPrice + drinksPrice
                val discountStr = discount.map(d => s"  - $d").getOrElse("  - None")
                val specialInfoStr = specialInfo.getOrElse("None")

                s"""|Order Summary:
                    |Name: $name
                    |Address: $address
                    |Phone: $phone
                    |
                    |Pizzas:
                    |$pizzasStr
                    |
                    |Extra Drinks:
                    |$drinksStr
                    |
                    |Total before discount:
                    |$totalBeforeDiscount
                    |
                    |Discount:
                    |$discountStr
                    |
                    |Total:
                    |${BigDecimal(price).setScale(2, BigDecimal.RoundingMode.HALF_UP).toDouble}
                    |
                    |Special Info: $specialInfoStr
                """.stripMargin
                }
        }
    }
}


@main
def run() =
    import pizzeria._
    import orders._

    val myPizza = Pizza(Margherita,Large,Thin, extraMeat=Option(Salami))
    //println(myPizza)
    //println(myPizza.price)

    val myOrder = Order("grześ", "ul. jakas 3", "+48111222333", List(myPizza), Map(), Option(Senior))
    //val myOrder2 = orders.Order("ala", "----", "+481112223334", List(myPizza), List(), Option(Senior))
    //val myOrder3 = orders.Order("basia", "----", "+111222333", List(myPizza), List(), Option(Senior))
    val myOrder4 = Order("jaś", "ul. jakas 5", "111222333", List(myPizza), Map(Lemonade -> 3), Option(Senior))
    println(myOrder)

    val myPizza2 = Pizza(Peperoni, Medium,Thick, extraTopping=Option(Garlic))
    val myOrder5 = Order("Cecylia", "abc", "323945421", List(myPizza, myPizza2), Map(Lemonade -> 5), specialInfo=Option("prosze pukac. Dzwonek nie dziala"))
    println(myOrder5)
