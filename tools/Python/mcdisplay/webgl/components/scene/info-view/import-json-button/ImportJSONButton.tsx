import React from "react";
import "../../../../common.css";
import "./import-json-button.css";
import { useInstrumentContext } from "../../../../Contexts/InstrumentContext";

const ImportJSONButton = () => {
  const { instrument, setInstrument } = useInstrumentContext();

  const handleButtonClick = () => {
    const comps = instrument.components;
    let element = document.createElement("a");
    element.setAttribute(
      "href",
      "data:text/plain;charset=utf-8," +
        encodeURIComponent(JSON.stringify(comps, null, 2))
    );
    element.setAttribute("download", "components.json");
    element.style.display = "none";
    document.body.appendChild(element);

    element.click();

    document.body.removeChild(element);
  };

  return (
    <div id="import-json-button" className="">
      <button onClick={handleButtonClick}>Import JSON</button>
    </div>
  );
};

export default ExportJSONButton;
