//> using dep "com.restfb:restfb:2025.10.0"
import scala.io.Source
import scala.concurrent.{Future, Await}
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._
import com.restfb._
import com.restfb.types.User
import java.io.{FileWriter, PrintWriter}
import java.time.LocalDateTime
import secrets._

val tokenPath = "../secrets/fb_token.txt"

object FacebookAdapter {
    private val myAppSecret = secrets.appSecret

    class MyFacebookClient(currentAccessToken: String)
        extends DefaultFacebookClient(
        currentAccessToken,
        myAppSecret,
        Version.VERSION_15_0)

    def getUser(accessToken: String, id: String): Future[User] = 
        Future {
        val client = new MyFacebookClient(accessToken)
        val user = client.fetchObject(id, classOf[User])
        user
    }

    def printToFile(logFile: String, user1: String, user2: String): Future[Unit] = 
        Future {
            val writer = new PrintWriter(new FileWriter(logFile, /* append = */ true))
            writer.write(s"${LocalDateTime.now().toString()}, $user1, $user2\n")
            writer.close()
        }

    def compareLikes(logFile: String, user1: String, user2: String): Unit = {
        val token = secrets.appAccessToken

        val user1F = getUser(token, user1)
        val user2F = getUser(token, user2)
        printToFile(logFile, user1, user2)

        val result = for {
            u1 <- user1F
            u2 <- user2F
        } yield {
            val likes1 = Option(u1.getLikes).map(_.getTotalCount).getOrElse(0)
            val likes2 = Option(u2.getLikes).map(_.getTotalCount).getOrElse(0)
            println(u1.getName)
            println(s"$user1 likes: $likes1 vs.\n$user2 likes: $likes2")
        }

        val resultF = Await.result(result, 10.seconds)
    }
}

@main
def run() = {
    // Example user IDs or "me" for current token user
    val user1 = "me"
    val user2 = "me"
    val logFile = "likes_comparison.log"

    FacebookAdapter.compareLikes(logFile, user1, user2)
}
