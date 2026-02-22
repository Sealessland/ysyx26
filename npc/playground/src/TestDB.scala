import org.chipsalliance.rvdecoderdb._
object TestDB extends App {
  // Let's use the local Instructions helper to see if it works
  val instTable = org.chipsalliance.rvdecoderdb.instructions(os.pwd / "riscv-opcodes")
  val add = instTable.find(_.name == "add").get
  println("ADD encoding: " + add.encoding.toString)
}
