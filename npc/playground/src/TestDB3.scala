import org.chipsalliance.rvdecoderdb._
object TestDB3 extends App {
  val instTable = org.chipsalliance.rvdecoderdb.instructions(os.pwd / "riscv-opcodes")
  val shifts = instTable.filter(i => Seq("srai", "slli").contains(i.name) && i.instructionSet.name == "rv32_i").toList
  shifts.foreach { i => 
    println(s"${i.name} in ${i.instructionSet.name}: env=${i.encoding.toString}")
  }
}
