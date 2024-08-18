import React from "react";
import "../../../../common.css";
import "./import-json-button.css";
import { useInstrumentContext } from "../../../../Contexts/InstrumentContext";

const ImportJSONButton = () => {
  const { instrument, setInstrument } = useInstrumentContext();

  const handleButtonClick = () => {
  };

  return (
    <div id="import-json-button" className="">
      <button onClick={handleButtonClick}>Import JSON</button>
    </div>
  );
};

export default ExportJSONButton;
