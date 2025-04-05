package plugins{
    trait TextPlugin {
        def transform(text: String): String
    }

    trait Reverting extends TextPlugin {
        abstract override def transform(text: String): String =
            super.transform(text.reverse)
    }

    trait LowerCasing extends TextPlugin {
        abstract override def transform(text: String): String =
            super.transform(text.toLowerCase)
    }

    trait SingleSpacing extends TextPlugin {
        abstract override def transform(text: String): String =
            super.transform(text.replaceAll("\\s+", " "))
    }

    trait NoSpacing extends TextPlugin {
        abstract override def transform(text: String): String =
            super.transform(text.replaceAll(" ", ""))
    }

    trait DuplicateRemoval extends TextPlugin {
        abstract override def transform(text: String): String = {
            val seen = scala.collection.mutable.Set[Char]()
            super.transform(text.filter { c =>
                val isNew = !seen.contains(c)
                seen += c
                isNew
            })
        }
    }

    trait Rotating extends TextPlugin {
        abstract override def transform(text: String): String =
            if (text.isEmpty) super.transform(text)
            else super.transform(s"${text.last}${text.init}")
    }

    trait Doubling extends TextPlugin {
        abstract override def transform(text: String): String =
            super.transform(text.zipWithIndex.map {
                case (c, i) => if (i % 2 == 1) s"$c$c" else c.toString
            }.mkString)
    }

    trait Shortening extends TextPlugin {
        abstract override def transform(text: String): String =
            super.transform(text.zipWithIndex.collect {
                case (c, i) if i % 2 == 0 => c
            }.mkString)
    }

    // Basic plugin class to compose with traits
    class BasicPlugin extends TextPlugin {
        override def transform(text: String): String = text
    }

    trait Pluginable {
        def plugin(text: String): String
    }

    object Actions {
        val actionA: Pluginable = new BasicPlugin
            with SingleSpacing
            with Doubling
            with Shortening with Pluginable {
                def plugin(text: String): String = transform(text)
        }

        val actionB: Pluginable = new BasicPlugin
            with NoSpacing
            with Shortening
            with Doubling with Pluginable {
                def plugin(text: String): String = transform(text)
            }

        val actionC: Pluginable = new BasicPlugin
            with LowerCasing
            with Doubling with Pluginable {
                def plugin(text: String): String = transform(text)
            }

        val actionD: Pluginable = new BasicPlugin
            with DuplicateRemoval
            with Rotating with Pluginable {
                def plugin(text: String): String = transform(text)
            }
    }
}