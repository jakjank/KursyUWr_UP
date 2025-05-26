val scala3Version = "3.7.0"

ThisBuild / scalafmtOnCompile := true
enablePlugins(
  ScalafmtPlugin,
  ScalafixPlugin)

lazy val root = project
  .in(file("."))
  .aggregate(core, blackjack)
  .dependsOn(core, blackjack)
  .settings(
    name := "lab9",
    version := "0.0.1",

    scalaVersion := scala3Version,

    libraryDependencies += "org.scalameta" %% "munit" % "1.0.0" % Test
  )

val commonScalaOptions = Seq(
  "-deprecation",
  "-Xfatal-warnings"
)

val core = project
  .enablePlugins(ScalafmtPlugin)
  .in(file("core"))
  .settings(
    name := "core",
    scalaVersion := scala3Version,
    scalacOptions ++= commonScalaOptions,
    libraryDependencies += "org.scalatest" %% "scalatest" % "3.2.19" % "test"
  )

val blackjack = project
  .enablePlugins(ScalafmtPlugin)
  .in(file("blackjack"))
  .settings(
    name := "blackjack",
    scalaVersion := scala3Version,
    scalacOptions ++= commonScalaOptions,
    libraryDependencies += "org.scalatest" %% "scalatest" % "3.2.19" % "test"
  )
  .dependsOn(core)