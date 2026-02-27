package sCore.utils

import chisel3._
import chisel3.util._

// -----------------------------------------------------------------------------
// AXI4-Lite 定义（最小化子集，仅支持单个 in-flight 事务）
// -----------------------------------------------------------------------------
class AxiLiteAddr(val addrBits: Int) extends Bundle {
  val addr = UInt(addrBits.W)
  val prot = UInt(3.W)
}

class AxiLiteWriteData(val dataBits: Int) extends Bundle {
  val data = UInt(dataBits.W)
  val strb = UInt((dataBits / 8).W)
}

class AxiLiteReadData(val dataBits: Int) extends Bundle {
  val data = UInt(dataBits.W)
  val resp = UInt(2.W)
}

class AxiLiteWriteResp extends Bundle {
  val resp = UInt(2.W)
}

class AxiLiteMasterIO(val addrBits: Int, val dataBits: Int) extends Bundle {
  val aw = Decoupled(new AxiLiteAddr(addrBits))
  val w  = Decoupled(new AxiLiteWriteData(dataBits))
  val b  = Flipped(Decoupled(new AxiLiteWriteResp))
  val ar = Decoupled(new AxiLiteAddr(addrBits))
  val r  = Flipped(Decoupled(new AxiLiteReadData(dataBits)))
}

// -----------------------------------------------------------------------------
// AXI4-Lite 仲裁器（串行化：一次只允许一个事务）
// -----------------------------------------------------------------------------
class AxiLiteArbiter(addrBits: Int, dataBits: Int, preferSecond: Boolean = true)
    extends Module {
  val io = IO(new Bundle {
    val in0 = Flipped(new AxiLiteMasterIO(addrBits, dataBits)) // 通常接 IF
    val in1 = Flipped(new AxiLiteMasterIO(addrBits, dataBits)) // 通常接 LSU
    val out = new AxiLiteMasterIO(addrBits, dataBits)
  })

  val sIdle :: sSendWrite :: sSendRead :: sWaitWriteResp :: sWaitReadResp :: Nil = Enum(5)
  val state = RegInit(sIdle)
  val grant1 = RegInit(false.B) // false -> in0, true -> in1
  val awDone = RegInit(false.B)
  val wDone  = RegInit(false.B)

  val in0WriteReq = io.in0.aw.valid || io.in0.w.valid
  val in1WriteReq = io.in1.aw.valid || io.in1.w.valid
  val in0ReadReq  = io.in0.ar.valid
  val in1ReadReq  = io.in1.ar.valid
  val in0Req = in0WriteReq || in0ReadReq
  val in1Req = in1WriteReq || in1ReadReq

  val sel1 = WireDefault(false.B)
  val selIsWrite = WireDefault(false.B)
  val selHasReq = WireDefault(false.B)

  when(preferSecond.B) {
    when(in1Req) {
      sel1 := true.B
      selIsWrite := in1WriteReq
      selHasReq := true.B
    } .elsewhen(in0Req) {
      sel1 := false.B
      selIsWrite := in0WriteReq
      selHasReq := true.B
    }
  } .otherwise {
    when(in0Req) {
      sel1 := false.B
      selIsWrite := in0WriteReq
      selHasReq := true.B
    } .elsewhen(in1Req) {
      sel1 := true.B
      selIsWrite := in1WriteReq
      selHasReq := true.B
    }
  }

  val selAw = Mux(grant1, io.in1.aw, io.in0.aw)
  val selW  = Mux(grant1, io.in1.w, io.in0.w)
  val selAr = Mux(grant1, io.in1.ar, io.in0.ar)
  val selB  = Mux(grant1, io.in1.b, io.in0.b)
  val selR  = Mux(grant1, io.in1.r, io.in0.r)

  // 默认值
  io.out.aw.bits  := selAw.bits
  io.out.w.bits   := selW.bits
  io.out.ar.bits  := selAr.bits
  io.out.aw.valid := false.B
  io.out.w.valid  := false.B
  io.out.ar.valid := false.B

  io.out.b.ready := false.B
  io.out.r.ready := false.B

  io.in0.aw.ready := false.B
  io.in0.w.ready  := false.B
  io.in0.ar.ready := false.B
  io.in0.b.valid  := false.B
  io.in0.r.valid  := false.B
  io.in0.b.bits   := io.out.b.bits
  io.in0.r.bits   := io.out.r.bits

  io.in1.aw.ready := false.B
  io.in1.w.ready  := false.B
  io.in1.ar.ready := false.B
  io.in1.b.valid  := false.B
  io.in1.r.valid  := false.B
  io.in1.b.bits   := io.out.b.bits
  io.in1.r.bits   := io.out.r.bits

  switch(state) {
    is(sIdle) {
      when(selHasReq) {
        grant1 := sel1
        when(selIsWrite) {
          state := sSendWrite
          awDone := false.B
          wDone  := false.B
        } .otherwise {
          state := sSendRead
        }
      }
    }

    is(sSendWrite) {
      io.out.aw.valid := !awDone && selAw.valid
      io.out.w.valid  := !wDone && selW.valid

      io.in0.aw.ready := !grant1 && !awDone && io.out.aw.ready
      io.in0.w.ready  := !grant1 && !wDone && io.out.w.ready
      io.in1.aw.ready := grant1 && !awDone && io.out.aw.ready
      io.in1.w.ready  := grant1 && !wDone && io.out.w.ready

      when(io.out.aw.fire) { awDone := true.B }
      when(io.out.w.fire)  { wDone  := true.B }

      val awDoneNext = awDone || io.out.aw.fire
      val wDoneNext  = wDone  || io.out.w.fire
      when(awDoneNext && wDoneNext) {
        state := sWaitWriteResp
      }
    }

    is(sSendRead) {
      io.out.ar.valid := selAr.valid
      io.in0.ar.ready := !grant1 && io.out.ar.ready
      io.in1.ar.ready := grant1 && io.out.ar.ready
      when(io.out.ar.fire) {
        state := sWaitReadResp
      }
    }

    is(sWaitWriteResp) {
      io.out.b.ready := selB.ready
      when(grant1) {
        io.in1.b.valid := io.out.b.valid
      } .otherwise {
        io.in0.b.valid := io.out.b.valid
      }
      when(io.out.b.fire) {
        state := sIdle
      }
    }

    is(sWaitReadResp) {
      io.out.r.ready := selR.ready
      when(grant1) {
        io.in1.r.valid := io.out.r.valid
      } .otherwise {
        io.in0.r.valid := io.out.r.valid
      }
      when(io.out.r.fire) {
        state := sIdle
      }
    }
  }
}
