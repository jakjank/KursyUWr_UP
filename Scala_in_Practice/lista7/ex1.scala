package money{
    trait Currency
    case object PLN extends Currency
    case object EUR extends Currency
    case object USD extends Currency
    val $ = USD
    // val € = EUR ???
    val euro = EUR
    val zl = PLN



    val conversion: Map[(Currency,Currency), BigDecimal] = Map(
        (PLN, EUR) -> BigDecimal("0.22"),
        (EUR, PLN) -> BigDecimal("4.55"),
        (PLN, USD) -> BigDecimal("0.25"),
        (USD, PLN) -> BigDecimal("4.0"),
        (EUR, USD) -> BigDecimal("1.08"),
        (USD, EUR) -> BigDecimal("0.91")
    )

    case class Money(val amount: BigDecimal, val currency: Currency){
        override def toString() =
            return s"$amount $currency"

        def +(other: Money): Money = {
            if(this.currency != other.currency){
                val rate = conversion.getOrElse((other.currency, this.currency),
                    throw new Exception(s"No conversion from ${other.currency} to ${this.currency}")
                )
                Money(this.amount+rate*other.amount, this.currency)
            } else{
                Money(this.amount+other.amount, this.currency)
            }
        }

        def -(other: Money): Money = {
            this + Money(-other.amount, other.currency)
        }

        def *(x: Double): Money = {
            Money(x*this.amount, this.currency)
        }

        def as(targetCurrency: Currency): Money = {
            if (this.currency == targetCurrency) {
                this
            } else {
                val rate = conversion.getOrElse((this.currency, targetCurrency),
                    throw new Exception(s"No conversion rate found from ${this.currency} to $targetCurrency")
                )
                Money(this.amount * rate, targetCurrency)
            }
        }

        def >(other: Money): Boolean = {
            if(this.currency != other.currency){
                val rate = conversion.getOrElse((other.currency, this.currency),
                throw new Exception(s"No conversion from ${other.currency} to ${this.currency}")
                )
                return this.amount > other.amount * rate
            }
            this.amount > other.amount
        }

        def <(other: Money): Boolean = {
            if(this.currency != other.currency){
                val rate = conversion.getOrElse((other.currency, this.currency),
                throw new Exception(s"No conversion from ${other.currency} to ${this.currency}")
                )
                return this.amount < other.amount * rate
            }
            this.amount < other.amount
        }
    }

    implicit class RichAmount(val amount: BigDecimal) extends AnyVal {
        def apply(currency: Currency): Money = Money(amount, currency)
    }
    implicit class RichIntAmount(val amount: Int) extends AnyVal {
        def apply(currency: Currency): Money = Money(BigDecimal(amount), currency)
    }
    implicit class RichDoubleAmount(val amount: Double) extends AnyVal {
        def apply(currency: Currency): Money = Money(BigDecimal(amount), currency)
    }
}

@main
def run() =
    import money._
    print("20.0(zl) + 5.1(EUR) = ")
    val x = 20.0(zl) + 5.1(EUR)
    println(x)

    print("50(USD) - 20(euro) = ")
    val y = 50(USD) - 20(euro)
    println(y)

    print(s"$x * 4 = ")
    val z = x * 3
    println(z)

    print(s"$z as EUR = ")
    val q = z as EUR
    println(q)

    print(s"$q > $y? ")
    println(q > y)


