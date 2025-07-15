// GhostMintVerseController.verse
class GhostMintVerseController {
  var Widget: widget::UserWidget;

  on BuildTx(inputs: array<UTxInput>, outputs: array<UTxOutput>, fee: int) {
    let txHex = Interface.BuildTransaction(inputs, outputs, fee);
    Widget.SetText('TxHexBox', txHex);
  }

  on InjectBlock() {
    // Call backend to process PoW and submit block
    Interface.InjectCurrentBlock();
  }
}
