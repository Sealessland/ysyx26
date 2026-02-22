import org.chipsalliance.rvdecoderdb._
object TestDB2 extends App {
  val instTable = org.chipsalliance.rvdecoderdb.instructions(os.pwd / "riscv-opcodes")
  val shifts = instTable.filter(i => Seq("srai", "slli", "srli", "ebreak").contains(i.name)).toList
  shifts.foreach { i => 
    println(s"${i.name} in ${i.instructionSet.name}: args=${i.args.map(_.name)}")
  }
}
