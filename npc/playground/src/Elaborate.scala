import sCore.CoreTop
import sCore.utils.{CoreConfig, FrontendConfig, LsuConfig}

object Elaborate extends App {
  def pickArg(prefix: String, args: Array[String]): Option[String] = {
    args.collectFirst {
      case s if s.startsWith(prefix) => s.substring(prefix.length)
    }
  }

  val fetchMode = pickArg("--fetch-mode=", args)
  val lsuMode = pickArg("--lsu-mode=", args)
  val passthroughArgs = args.filterNot(a => a.startsWith("--fetch-mode=") || a.startsWith("--lsu-mode="))

  val firtoolOptions = Array(
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )

  implicit val config: CoreConfig = CoreConfig(
    hasM = true,
    fastMdu = true,
    hasZicsr = true,
    frontend = FrontendConfig(fetchMode = fetchMode.getOrElse(FrontendConfig().fetchMode)),
    lsu = LsuConfig(lsuMode = lsuMode.getOrElse(LsuConfig().lsuMode))
  )

  // 2. 生成主要模块的Verilog代码
  circt.stage.ChiselStage.emitSystemVerilogFile(new CoreTop(), passthroughArgs, firtoolOptions)
}
