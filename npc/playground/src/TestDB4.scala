import org.chipsalliance.rvdecoderdb._
object TestDB4 extends App {
  val instTable = org.chipsalliance.rvdecoderdb.instructions(os.pwd / "riscv-opcodes")
  val shifts = instTable.filter(i => Seq("srai", "slli", "srli").contains(i.name) && i.instructionSet.name == "rv32_i").toList
  shifts.foreach { i => 
    println(s"${i.name} in ${i.instructionSet.name}: env=${i.encoding.toString} args=${i.args.map(_.name)}")
  }
}
