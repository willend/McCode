import React from "react";
import "../../../../common.css";
import "./import-json-button.css";
import { useInstrumentContext } from "../../../../Contexts/InstrumentContext";

const ImportJSONButton = () => {
  const { instrument, setInstrument } = useInstrumentContext();

  const handleButtonClick = () => {
      // Get the form and file field
      let form = document.querySelector('#upload');
      let file = document.querySelector('#file');
      // Listen for submit events
      form.addEventListener('submit', handleSubmit);
      // Stop the form from reloading the page
      event.preventDefault();
      
      // If there's no file, do nothing
      if (!file.value.length) return;
      
      // Create a new FileReader() object
      let reader = new FileReader();
      
      // Read the file
      reader.readAsText(file.files[0]);
  };

  return (
    <div id="import-json-button" className="">
      <button onClick={handleButtonClick}>Import JSON</button>
    </div>
  );
};

export default ExportJSONButton;
