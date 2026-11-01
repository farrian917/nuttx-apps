# V0.97 offline AOT expansion

Added ROM-derived decoding and native C generation for 13 families: MOVE.B abs->abs, MOVE.W d16(An)->abs, ADD.L Dn->abs, MOVE.L indexed->abs, ASR.W #2,Dn, SUBA.W Dn, ADDA.W immediate, MOVE.W postinc->abs, MOVE.L postinc->postinc, LEA displacement, MOVE.W immediate->postinc, MOVE.B Dn->postinc, MOVEA.L indexed->An. The 0x009436 instruction is now generated. Added no runtime interpreter.

The generated CFG may expose further unsupported code and indirect JSR destinations. Hardware is not verified. This release is not guaranteed to complete IRQ6 or render graphics. Host C syntax checker validates generated code only.
